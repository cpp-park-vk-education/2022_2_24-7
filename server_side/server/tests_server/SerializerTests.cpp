#include <gtest/gtest.h>

#include "ISerializer.hpp"
#include "Serializer.hpp"

TEST(DISABLED_SerializerTest, CanSaveRequest)
{
    Serializer ser;
    boost::asio::streambuf buf;
    Request req;
    std::ostream os(&buf);
    os << "some_command";
    ser.save(buf, req);
    EXPECT_EQ(req.command, "some_command");
}

TEST(DISABLED_SerializerTest, CanLoadReply)
{
    Serializer ser;
    boost::asio::streambuf buf;
    Reply rep = { "some_command" };
    ser.load(buf, rep);
    std::string ostr;
    std::istream(&buf) >> ostr;
    EXPECT_EQ(ostr, "some_command");
}
