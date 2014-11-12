#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <assert.h>

namespace fs {

/**
 * @brief command from client
 */
class Command
{
public:

    Command() = delete;

    Command(const char* msg, std::size_t len)
    {
        assert(msg);
        assert(len > 2);    //at least "\r\n"

        parse_and_init(msg);
    }

    const std::string& code()const
    {
        return code_;
    }

    const std::string& argument()const
    {
        return argt_;
    }

private:
    std::string code_;
    std::string argt_;

    void parse_and_init(const char* msg)
    {
        auto ch = msg;
        for(;       *ch != ' ';     ++ch)   code_.push_back(*ch);
        for(++ch;   *ch != '\r';    ++ch)   argt_.push_back(*ch);
    }
};

inline std::ostream&
operator <<(std::ostream& os, const Command& c)
{
    os << "[" << c.code()       << "]"
       << "[" << c.argument()   << "]";
    return os;
}
}//namespace

#endif // COMMAND_HPP

//! @test
//!
//#include <iostream>
//#include "command.hpp"
//int main()
//{
//    fs::Command cmd{"SYST ba1234\r\n",13};
//    std::cout << cmd;
//    return 0;
//}
//! @output
//[SYST][ba1234]
