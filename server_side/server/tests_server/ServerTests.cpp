#include <gmock/gmock.h>

#include "Serializer.hpp"
#include "Server.hpp"

class MockServer : public IServer {
   public:
    MOCK_METHOD0(start_accept, void());
    MOCK_METHOD1(handle_accept, void(const boost::system::error_code&));
    MOCK_METHOD0(handle_stop, void());
    MOCK_METHOD0(run, void());
};

// мокать только внешние зависимости
// не тестировать, что не мое

TEST(ServerTest, StartServer) {
    MockServer server;

    EXPECT_CALL(server, start_accept).Times(1);
    // EXPECT_CALL(server, handle_accept).Times(1);
    EXPECT_CALL(server, handle_stop).Times(1);
    EXPECT_CALL(server, run).Times(1);

    server.start_accept();
    // server.handle_accept();
    server.handle_stop();
    server.run();
}
