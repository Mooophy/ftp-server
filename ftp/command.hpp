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

    Command(const char* msg, std::size_t len):
        code_{},argt_{}
    {
        len -= 2;   //remove "\r\n"

        unsigned idx=0;
        for(    ; idx!=len && !std::isspace(msg[idx]); ++idx)
            code_.push_back(msg[idx]);

        if(idx<len)
            for(++idx;  idx!=len;   ++idx)  argt_.push_back(msg[idx]);
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
};

inline bool operator !=(const Command& lhs, const std::string& rhs)
{
    return lhs.code() != rhs;
}

inline bool operator !=(const std::string& lhs, const Command& rhs)
{
    return lhs != rhs.code();
}

inline bool operator ==(const Command& lhs, const std::string& rhs)
{
    return lhs.code() == rhs;
}

inline bool operator ==(const std::string& lhs, const Command& rhs)
{
    return lhs == rhs.code();
}

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
