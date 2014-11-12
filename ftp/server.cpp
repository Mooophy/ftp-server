#include <thread>
#include "server.hpp"
#include "session.hpp"

void fs::Server::run()
{
    std::cout << ">server is running" << std::endl;
    while(true)
    {
        Tcp::socket soc(io_service_);
        acceptor_.accept(soc);
        std::cout << ">new session established" << std::endl;

        std::thread{Session{}, std::move(soc)}.detach();
    }
}