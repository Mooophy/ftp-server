#ifndef SERVER_HPP
#define SERVER_HPP

#include <memory>
#include "alias_for_boost.hpp"
#include "users.hpp"

namespace fs {

class Server
{
public:
    using SharedUserTable = std::shared_ptr<fs::Users>;

    Server() = delete;

    explicit Server(unsigned short port):
        io_service_{},
        acceptor_{io_service_, Tcp::endpoint{Tcp::v4(), port}},
        user_table_{std::make_shared<fs::Users>("users")}
    {
        run();
    }

private:
    Io_service io_service_;
    Acceptor acceptor_;
    SharedUserTable user_table_;

    void run();
    void make_new_session(Tcp::socket&& soc)const;
};

}//namespace
#endif // SERVER_HPP
