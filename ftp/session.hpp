#ifndef SESSION_HPP
#define SESSION_HPP

#include "alias_for_boost.hpp"
#include "users.hpp"

namespace fs{

class Session
{
public:
    using SharedUserTable = std::shared_ptr<fs::Users>;

    Session(Tcp::socket soc, SharedUserTable users):
        socket_{std::move(soc)},
        user_table_{users}
    {}

    void operator ()()
    {

    }

private:
    Tcp::socket socket_;
    SharedUserTable user_table_;

};

}//namespace
#endif // SESSION_HPP
