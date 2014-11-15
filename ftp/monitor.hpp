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
        this_thread_{   [this]{run();}  }
    {}

    ~Monitor()
    {
        this_thread_.join();
    }

private:
    const Server* server_;
    std::thread this_thread_;

    void run() const
    {
        while(server_)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds{1000});

            std::string stat{"threads : ["};
            stat += std::to_string(server_->threads_vector_.size());
            stat += "]   data sockets : [";
            stat += std::to_string(server_->data_sockets_->size());
            stat += "]";
            server_->print_safely(stat) << std::endl;
        }
    }
};

}//namespace
#endif // MONITOR_HPP
