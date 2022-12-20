#include <gmock/gmock.h>

#include "Connection.hpp"
#include "Serializer.hpp"

class MockConnection : public IConnection {
   public:
    MOCK_METHOD1(handle_read, void(const boost::system::error_code&));
    MOCK_METHOD1(handle_write, void(const boost::system::error_code&));
    MOCK_METHOD0(start, void());
    MOCK_METHOD0(get_socket, boost::asio::ip::tcp::socket&());
};

TEST(ConnectionTest, StartConnection) {
    MockConnection connect;
    
    EXPECT_CALL(connect, start).Times(1);
    // EXPECT_CALL(connect, handle_read).Times(1);
    // EXPECT_CALL(connect, handle_write).Times(1);
    // EXPECT_CALL(connect, get_socket).Times(1);

    connect.start();
    // connect.handle_read();
    // connect.handle_write();
    // connect.get_socket();
}
