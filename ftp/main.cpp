#include "server.hpp"
#include "monitor.hpp"


int main()
{
    fs::Server server;
    fs::Monitor monitor{&server};

    return 0;
}

