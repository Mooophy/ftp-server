#ifndef ALIAS_FOR_BOOST_HPP
#define ALIAS_FOR_BOOST_HPP

#include <boost/asio.hpp>

namespace fs {

using Tcp           =   boost::asio::ip::tcp;
using Acceptor      =   Tcp::acceptor;
using Io_service    =   boost::asio::io_service;

}

#endif // ALIAS_FOR_BOOST_HPP
