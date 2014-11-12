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

        make_new_session(std::move(soc));
    }
}

void fs::Server::make_new_session(Tcp::socket&& soc)const
{
    auto t = std::thread{ Session{std::move(soc)} };
    t.detach();
}
