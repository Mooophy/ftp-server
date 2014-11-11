#include <iostream>
#include "users.hpp"

int main()
{
    fs::Users users{"users"};
    users.print();

    std::cout << users.check("alan","1234") << std::endl;

    return 0;
}

