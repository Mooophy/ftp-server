#ifndef SESSION_HPP
#define SESSION_HPP

#include "alias_for_boost.hpp"
#include "users.hpp"


namespace fs{

class Session
{
public:
    Session(Tcp::socket soc, const fs::Users* users):
        socket_{std::move(soc)},
        user_table_{users}
    {}

    void operator ()()
    {
        //not implemented yet.
    }

private:
    Tcp::socket socket_;
    const fs::Users* user_table_;

};

}//namespace
#endif // SESSION_HPP
