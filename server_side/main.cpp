#include <thread>
#include <vector>

#include "Router.hpp"
#include "Server.hpp"
#include "WorkWithData.hpp"

static inline constexpr int THREADS_NUM = 10;

boost::asio::io_context context;

void server_threads_spawn() { context.run(); }

int main(int argc, char *argv[]) {
    unsigned int port = argc > 1 ? std::stol(argv[1]) : default_port;

    WorkWithData workWithData;
    Router router(&workWithData);
    
    Server server(context, router, port);
    server.start();

    std::vector<std::thread> thread_pool;
    for (int i = 0; i < THREADS_NUM; ++i) {
        thread_pool.emplace_back(server_threads_spawn);
    }

    for (std::thread &thr : thread_pool) {
        thr.join();
    }
    return 0;
}
