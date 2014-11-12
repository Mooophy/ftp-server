#ifndef SESSION_HPP
#define SESSION_HPP

#include "alias.hpp"
#include "users.hpp"

namespace fs {

const int MAX_LENGTH = 1024;

class Session
{
public:

    Session():
        all_users_{}
    {}

    void operator ()(Tcp::socket soc) const
    {
        using boost::asio::write;
        try
        {
            while(true)
            {
                char data[MAX_LENGTH];

                boost::system::error_code error;
                size_t length = soc.read_some(boost::asio::buffer(data), error);

                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.

                std::cout << ">from client : " << data << std::endl;

                boost::asio::write(soc, boost::asio::buffer(data, length));
            }
        }
        catch (std::exception& e)
        {
            std::cerr << ">exception in thread: " << e.what() << "\n";
        }
    }

private:
    fs::Users all_users_;
};
}//namespace

#endif // SESSION_HPP
