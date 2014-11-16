#ifndef SESSION_HPP
#define SESSION_HPP

#include <mutex>
#include "alias_for_boost.hpp"
#include "users.hpp"
#include "command.hpp"


namespace fs{

class Session
{
public:
    using Lock = std::unique_lock<std::mutex>;

    Session(Tcp::socket soc,
            const fs::Users* users,
            std::mutex* m):
        socket_{std::move(soc)},
        user_table_{users},
        mutex_{m}
    {}

    void operator()()
    {
        do_session();
    }

private:
    Tcp::socket socket_;
    const fs::Users* user_table_;
    std::mutex* mutex_;

    Lock lock() const
    {
        return Lock{*mutex_};
    }

    template<typename Printable>
    std::ostream& print_safely(const Printable& to_print) const
    {
        auto this_scope = lock();
        return  std::cout << to_print << std::flush;
    }

    Command read()
    {
        char data[BUFF_SIZE];
        boost::system::error_code error;
        size_t length = socket_.read_some(boost::asio::buffer(data), error);

        if (error == boost::asio::error::eof)   return Command{"eof",3};    // Connection closed cleanly by peer.
        else if (error)     throw boost::system::system_error(error);       // Some other error.

        {
            auto this_scope = lock();
            std::cout << "data received : "     <<  data
                      << "len = "               <<  length
                      << std::endl;
        }

        return Command{data,length};
    }

    void write(const std::string& response)
    {
        boost::asio::write(socket_, boost::asio::buffer(response));
    }

    bool prompt_and_check_password()
    {
        write("220 welcome to Yue Wang's FTP site\r\n");
        auto user = read().argument();
        write("331 password pls.\r\n");
        auto pwd = read().argument();

        return user_table_->check(user, pwd);
    }

    void do_session()
    {
        while(1);
    }
};

}//namespace
#endif // SESSION_HPP
