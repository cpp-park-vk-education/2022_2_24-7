#include <gtest/gtest.h>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Connection.hpp"
#include "Handler.hpp"
#include "IProject.hpp"
#include "IResponse.hpp"
#include "IRouter.hpp"
#include "IWorkWithData.hpp"
#include "Project.hpp"
#include "Reply.hpp"
#include "Request.hpp"
#include "Router.hpp"
#include "Server.hpp"

TEST(DefaultTest, Test) { EXPECT_EQ((2 * 2), 4); }

// TEST(ProjectConnectTests, AttachNewConnection) {
//     Router routerTest;
//     Project projectTest;
//     // connectionIdCounter = 0, projectConnections is empty
//     boost::asio::io_context io_context_;
//     ConnectionPtr userConnection = new Connection(io_context_, routerTest);
//     projectTest.ConnectUser(userConnection);

//     EXPECT_EQ(projectTest.ConnectionExist(userConnection), true);
//     EXPECT_EQ(projectTest.GetCounter(), 1);
//     EXPECT_EQ(projectTest.FindConnectionId(userConnection), 0);
//     EXPECT_EQ(projectTest.GetProjectConnections().size(), 1);
// }
