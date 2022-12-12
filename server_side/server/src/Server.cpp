#include "Server.hpp"

#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>

#include "Connection.hpp"

void Server::start_accept() {
    newConnection.reset(new Connection(service, serializer, router));
    connections.push_back(newConnection);
    acceptor.async_accept(newConnection->get_socket(),
                          boost::bind(&Server::handle_accept, this, boost::asio::placeholders::error));
}

void Server::handle_accept(const boost::system::error_code& e) {
    std::cout << "handle_accept" << std::endl;
    if (!e) {
        newConnection->start();
    }

    start_accept();
}

void Server::handle_stop() { service.stop(); }

Server::Server(ISerializer& ser, IRouter& router)
    : signals(service),
      acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001)),
      serializer(ser),
      router(router) {
    signals.add(SIGINT);
    signals.add(SIGTERM);
#if defined(SIGQUIT)
    signals.add(SIGQUIT);
#endif  // defined(SIGQUIT)
    signals.async_wait(boost::bind(&Server::handle_stop, this));

    start_accept();
}

void Server::run() {
    std::vector<boost::shared_ptr<boost::thread>> threads;
    for (std::size_t i = 0; i < 10; ++i) {
        boost::shared_ptr<boost::thread> thread(
            new boost::thread(boost::bind(&boost::asio::io_service::run, &service)));
        threads.push_back(thread);
    }

    for (std::size_t i = 0; i < threads.size(); ++i) threads[i]->join();
}
