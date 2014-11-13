#ifndef SESSION_HPP
#define SESSION_HPP

#include "alias_for_boost.hpp"
#include "command.hpp"

namespace fs {

const int MAX_LENGTH = 1024;

class Session
{
public:

    explicit Session(Tcp::socket soc):
        socket_{std::move(soc)}
    {}

    void operator ()()
    {
        do_session();
    }

private:
    Tcp::socket socket_;

    void do_session();
    Command read();

};
}//namespace

#endif // SESSION_HPP
