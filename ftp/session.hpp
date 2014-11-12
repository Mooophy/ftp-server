#ifndef SESSION_HPP
#define SESSION_HPP

#include "alias.hpp"
#include "users.hpp"

namespace fs {

const int MAX_LENGTH = 1024;

class Session
{
public:

    explicit Session(Tcp::socket soc):
        all_users_{},
        socket_{std::move(soc)}
    {}

    void operator ()()
    {
        do_session();
    }

private:
    fs::Users all_users_;
    Tcp::socket socket_;

    void do_session();
};
}//namespace

#endif // SESSION_HPP
