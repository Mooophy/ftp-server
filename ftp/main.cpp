#include <iostream>
#include "command.hpp"
int main()
{
    fs::Command cmd{"SYST ba1234\r\n",13};
    std::cout << cmd.code() << std::endl << cmd.argument() << std::endl;
    return 0;
}

