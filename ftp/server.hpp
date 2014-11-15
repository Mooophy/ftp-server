#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <memory>
#include <thread>
#include <mutex>
#include "alias_for_boost.hpp"
#include "users.hpp"


namespace fs{

class Server
{
public:
    using SharedUserTable   =   std::shared_ptr<fs::Users>;
    using SocketsMap        =   std::map<Tcp::endpoint, Tcp::socket>;
    using SharedSocketsMap  =   std::shared_ptr<SocketsMap>;
    using ThreadVector      =   std::vector<std::thread>;
    using Lock              =   std::unique_lock<std::mutex>;

    Server():
        Server(1234,5678)
    {}

    Server(unsigned short ctrl_port, unsigned short data_port):
        user_table_{std::make_shared<fs::Users>("users")},
        io_service_{},
        ctrl_acceptor_{io_service_, Tcp::endpoint{Tcp::v4(), ctrl_port}},
        data_acceptor_{io_service_, Tcp::endpoint{Tcp::v4(), data_port}},
        data_sockets_{std::make_shared<SocketsMap>()},
        threads_vector_{}
    {
        add_thread(make_thread_for_data_acceptor());
    }

    ~Server()
    {
        wait_for_all_done();
    }

private:

    static std::mutex   m_;
    SharedUserTable     user_table_;
    Io_service          io_service_;

    Acceptor            ctrl_acceptor_;
    Acceptor            data_acceptor_;
    SharedSocketsMap    data_sockets_;
    ThreadVector        threads_vector_;

    void add_thread(std::thread&& t)
    {
        threads_vector_.push_back(std::move(t));
    }

    void wait_for_all_done()
    {
        for(auto& t : threads_vector_)  t.join();
    }

    Lock lock()
    {
        return Lock{m_};
    }

    template<typename Printable>
    std::ostream& print_safely(const Printable& something)
    {
        auto this_scope = lock();
        return    std::cout << something << std::flush;
    }

    std::thread make_thread_for_data_acceptor()
    {
        return std::thread
        {
            [this]{
                print_safely("waiting for new data connections") << std::endl;
                for(;;)
                {
                    Tcp::socket soc(io_service_);
                    data_acceptor_.accept(soc);
                    std::cout << ">new data socket generated" << std::endl;

                    using Element = std::pair<Tcp::endpoint, Tcp::socket>;
                    data_sockets_->insert(std::move(Element({soc.remote_endpoint(), std::move(soc)})));
                }
            }
        };
    }
};

//std::mutex Server::m_;

}//namespace
#endif // SERVER_HPP
