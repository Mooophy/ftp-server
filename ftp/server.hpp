#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

namespace fs {

using Tcp           =   boost::asio::ip::tcp;
using Acceptor      =   Tcp::acceptor;
using Io_service    =   boost::asio::io_service;

const int max_length = 1024;

void session(Tcp::socket sock)
{
    try
    {
        while(true)
        {
            char data[max_length];
            boost::system::error_code error;
            size_t length = sock.read_some(boost::asio::buffer(data), error);

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::cout << ">from client : " << data << std::endl;

            boost::asio::write(sock, boost::asio::buffer(data, length));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

class Server
{
public:
    Server() = delete;

    explicit Server(unsigned short port):
        io_service_{},
        acceptor_{io_service_, Tcp::endpoint{Tcp::v4(), port}}
    {
        run();
    }

private:
    Io_service io_service_;
    Acceptor acceptor_;

    void run()
    {
        std::cout << ">server is running" << std::endl;
        while(true)
        {
            Tcp::socket soc(io_service_);
            acceptor_.accept(soc);

            std::cout << "new session established" << std::endl;
            std::thread(session, std::move(soc)).detach();
        }
    }
};

}//namespace
#endif // SERVER_HPP
