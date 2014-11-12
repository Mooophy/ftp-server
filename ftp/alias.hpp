#ifndef ALIAS_HPP
#define ALIAS_HPP

#include <boost/asio.hpp>

namespace fs {

using Tcp           =   boost::asio::ip::tcp;
using Acceptor      =   Tcp::acceptor;
using Io_service    =   boost::asio::io_service;

}

#endif // ALIAS_HPP
