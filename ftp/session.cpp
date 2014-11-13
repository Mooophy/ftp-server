#include "session.hpp"
#include "command.hpp"

void fs::Session::do_session()
{
    using boost::asio::write;

    try
    {
        std::string prompt{"220 welcome to Yue Wang's FTP site\r\n"};

        while(1);   //mark : stopped here -->commands table

        while(true)
        {
            auto cmd = read();
            if(cmd.code() == "err") break;

            std::cout << ">from client : " << cmd << std::endl;
            std::string reply{"210\r\n"};
            write(socket_, boost::asio::buffer(reply, reply.size()));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << ">exception in thread: " << e.what() << "\n";
    }
}

fs::Command fs::Session::read()
{
    char data[MAX_LENGTH];

    boost::system::error_code error;
    size_t length = socket_.read_some(boost::asio::buffer(data), error);

    if (error == boost::asio::error::eof)
        return Command{"err",3}; // Connection closed cleanly by peer.
    else if (error)
        throw boost::system::system_error(error); // Some other error.

    return Command{data,length};
}
