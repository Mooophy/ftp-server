#ifndef MONITOR_HPP
#define MONITOR_HPP

#include <chrono>
#include "server.hpp"


namespace fs{

class Monitor
{
public:
    Monitor(const Server* s):
        server_{s},
        thread_for_monitor{   [this]{run();}  }
    {}

    ~Monitor()
    {
        thread_for_monitor.join();
    }

private:
    const Server* server_;
    std::thread thread_for_monitor;

    void run() const
    {
        while(server_)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds{1000});
            server_->print_safely(get_server_status());
        }
    }

    std::string get_server_status() const
    {
        if(!server_)    return "no server pointed to";

        std::string stat{"threads : ["};
        stat += std::to_string(server_->threads_vector_.size());
        stat += "]   data sockets : [";
        stat += std::to_string(server_->data_sockets_->size());
        stat += "]\n";

        return stat;
    }
};

}//namespace
#endif // MONITOR_HPP
