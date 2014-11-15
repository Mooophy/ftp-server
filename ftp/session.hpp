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
        boost::asio::write(socket_, boost::asio::buffer("210\r\n"));
        while(1);
    }

private:
    Tcp::socket socket_;
    const fs::Users* user_table_;

};

}//namespace
#endif // SESSION_HPP
