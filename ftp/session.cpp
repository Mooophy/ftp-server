#include <thread>
#include "session.hpp"
#include "command.hpp"

void fs::Session::do_session()
{
    try
    {
        if(!prompt_and_check_password())    return;

        write("230 User logged in.\r\n");
        for(auto cmd = read();/*  */; cmd = read())
        {
            if(cmd == "QUIT")
            {
                write("211 Bye.\r\n");          break;
            }

            if(cmd == "SYST")
            {
                write("215 Ubuntu 14.04\r\n");  continue;
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << ">exception in thread: " << e.what() << "\n";
    }

    auto id = std::this_thread::get_id();
    std::cout << "\n>thread [" << id <<"] exit" << std::endl;
}

bool fs::Session::prompt_and_check_password()
{
    write("220 welcome to Yue Wang's FTP site\r\n");
    auto user = read().argument();
    write("331 password pls.\r\n");
    auto pwd = read().argument();

    return user_table_->check(user, pwd);
}

void fs::Session::write(const std::string & response)
{
    boost::asio::write(socket_, boost::asio::buffer(response));
}

fs::Command fs::Session::read()
{
    char data[MAX_LENGTH];

    boost::system::error_code error;
    size_t length = socket_.read_some(boost::asio::buffer(data), error);

    std::cout << "data received : "     <<  data
              << "len = "               <<  length
              << std::endl << std::endl;

    if (error == boost::asio::error::eof)
        return Command{"err",3}; // Connection closed cleanly by peer.
    else if (error)
        throw boost::system::system_error(error); // Some other error.

    return Command{data,length};
}
