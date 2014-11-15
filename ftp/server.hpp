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
    using SharedUserTable = std::shared_ptr<fs::Users>;
    using SocketsMap = std::map<Tcp::endpoint, Tcp::socket>;
    using SharedSocketsMap = std::shared_ptr<SocketsMap>;
    using ThreadVector = std::vector<std::thread>;

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
    {}

private:

    static std::mutex m;
    SharedUserTable user_table_;
    Io_service  io_service_;

    Acceptor ctrl_acceptor_;
    Acceptor data_acceptor_;
    SharedSocketsMap data_sockets_;
    ThreadVector threads_vector_;
};

std::mutex Server::m;

}//namespace
#endif // SERVER_HPP
