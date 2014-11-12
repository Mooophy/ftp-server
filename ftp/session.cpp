#include "session.hpp"

void fs::Session::do_session()
{
    using boost::asio::write;

    try
    {
        while(true)
        {
            char data[MAX_LENGTH];

            boost::system::error_code error;
            size_t length = socket_.read_some(boost::asio::buffer(data), error);

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::cout << ">from client : " << data << std::endl;

            boost::asio::write(socket_, boost::asio::buffer(data, length));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << ">exception in thread: " << e.what() << "\n";
    }
}

