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
    std::thread t{ Session{std::move(soc), user_table_} };
    std::cout << "thread[" << t.get_id() << "] created\n";
    t.detach();
}
