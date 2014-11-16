#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <memory>
#include <thread>
#include <mutex>
#include "alias_for_boost.hpp"
#include "users.hpp"
#include "session.hpp"


namespace fs{

class Server
{
    friend class Monitor;
public:
    using UserTable     =   fs::Users;
    using SocketsMap    =   std::map<Tcp::endpoint, Tcp::socket>;
    using ThreadVector  =   std::vector<std::thread>;
    using Lock          =   std::unique_lock<std::mutex>;
    using SocketElement =   std::pair<Tcp::endpoint, Tcp::socket>;

    Server():
        Server(1234,5678)
    {}

    Server(unsigned short ctrl_port,
           unsigned short data_port,
           const std::string& fn = "users"):
        user_table_{fn},
        io_service_{},
        ctrl_acceptor_{io_service_, Tcp::endpoint{Tcp::v4(), ctrl_port}},
        data_acceptor_{io_service_, Tcp::endpoint{Tcp::v4(), data_port}},
        data_sockets_{},
        threads_vector_{}
    {
        add_thread_safely(make_thread_for_data_acceptor());
        add_thread_safely(make_thread_for_ctrl_acceptor());
    }

    ~Server()
    {
        wait_for_all_done();
    }

private:

    static std::mutex   mutex_;
    UserTable           user_table_;
    Io_service          io_service_;

    Acceptor            ctrl_acceptor_;
    Acceptor            data_acceptor_;
    SocketsMap          data_sockets_;
    ThreadVector        threads_vector_;

    Lock lock() const
    {
        return Lock{mutex_};
    }

    template<typename Printable>
    std::ostream& print_safely(const Printable& to_print) const
    {
        auto this_scope = lock();
        return  std::cout << to_print << std::flush;
    }

    void add_thread_safely(std::thread&& t)
    {
        auto this_scope = lock();
        threads_vector_.push_back(std::move(t));
    }

    void add_socket_safely(SocketElement&& elem)
    {
        auto this_scope = lock();
        data_sockets_.insert(std::move(elem));
    }

    void wait_for_all_done()
    {
        for(auto& t : threads_vector_)  t.join();
    }

    std::thread make_thread_for_ctrl_acceptor()
    {
        return std::thread
        {
            [this]{
                print_safely(">waiting for new ctrl connections\n");
                for(;;)
                {
                    Tcp::socket soc{io_service_};
                    ctrl_acceptor_.accept(soc); //<--blocking

                    std::thread new_ctrl_session{
                        fs::Session{std::move(soc), &user_table_}
                    };
                    print_safely ( ">new ctrl session generated\n") ;
                    add_thread_safely(std::move(new_ctrl_session));
                }
            }
        };
    }

    std::thread make_thread_for_data_acceptor()
    {
        return std::thread
        {
            [this]{
                print_safely(">waiting for new data connections\n");
                for(;;)
                {
                    Tcp::socket soc(io_service_);
                    data_acceptor_.accept(soc); //<--blocking
                    print_safely ( ">new data socket generated\n");

                    SocketElement elem{soc.remote_endpoint(), std::move(soc)};
                    add_socket_safely(std::move(elem));
                }
            }
        };
    }
};//class
}//namespace
#endif // SERVER_HPP
