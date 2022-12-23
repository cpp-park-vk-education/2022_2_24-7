#include "Client.hpp"

#include <boost/asio.hpp>

int main() {
    boost::asio::io_context context;

    Client client(context);
    client.start();

    return 0;
}