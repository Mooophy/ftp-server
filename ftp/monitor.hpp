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
        this_thread_{   [this]{run();}}
    {}

    void run() const
    {
        do_run();
    }

    ~Monitor()
    {
        this_thread_.join();
    }

private:
    const Server* server_;
    std::thread this_thread_;

    void do_run() const
    {
        while(server_)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds{1500});

            std::string info{"threads : ["};
            info += std::to_string(server_->threads_vector_.size());
            info += "]   data sockets : [";
            info += std::to_string(server_->data_sockets_->size());
            info += "]";
            server_->print_safely(info) << std::endl;
        }
    }
};

}//namespace
#endif // MONITOR_HPP
