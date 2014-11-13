#ifndef SESSION_HPP
#define SESSION_HPP

#include "alias_for_boost.hpp"
#include "users.hpp"
#include "command.hpp"

namespace fs {

const int MAX_LENGTH = 1024;

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
        do_session();
    }

private:
    Tcp::socket socket_;
    SharedUserTable user_table_;

    void do_session();
    Command read();
    void write(const std::string& response);
    bool prompt_and_check_password();
};
}//namespace

#endif // SESSION_HPP
