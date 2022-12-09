#include "Connection.hpp"

void Connection::handle_read()
{

}

void Connection::handle_write()
{

}

Connection::Connection(boost::asio::io_service& io_service, IRouter& router)
    : socket(io_service),
      router(router)
{

}

void Connection::start()
{

}

void Connection::get_socket()
{

}
