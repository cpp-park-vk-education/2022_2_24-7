#include <thread>

#include "Client.hpp"

boost::asio::io_context context;

void server_threads_spawn() { context.run(); }

int main() {
    std::shared_ptr<Client> client = std::make_shared<Client>(context);
    client->start();

    std::thread t(server_threads_spawn);
    t.join();

    return 0;
}
