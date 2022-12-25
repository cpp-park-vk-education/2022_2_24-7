#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

#include "../../server/include/Connection.hpp"
#include "../../server/include/Handler.hpp"
#include "../../server/include/Server.hpp"
#include "../../text_editor/interfaces/IWorkWithData.hpp"
#include "IProject.hpp"
#include "IResponse.hpp"
#include "IRouter.hpp"
#include "Project.hpp"
#include "Reply.hpp"
#include "Request.hpp"
#include "Router.hpp"

// TEST(BackendConstructorsTest, RouterConstructorTest) {
//     Router routerTest;
//     EXPECT_EQ(routerTest.GetProject()->GetPath(), "./files");
//     EXPECT_NE(routerTest.GetWorkWithData(), nullptr);
// }

TEST(BackendConstructorsTest, ProjectConstructorTest) {
    Project projectTest;
    EXPECT_EQ(projectTest.GetPath(), "./files");
    EXPECT_EQ(projectTest.GetName(), "project");
    EXPECT_EQ(projectTest.GetCounter(), 0);
}

TEST(ResponseTest, TestAll) {
    std::string replString = "insert";
    std::string reqString = "delete";
    Reply replyIt(replString);
    Request requestIt(reqString);

    EXPECT_EQ(replyIt.command, replString);
    EXPECT_EQ(requestIt.command, reqString);

    EXPECT_EQ(replyIt.GetMethod(), replString[0]);
    EXPECT_EQ(requestIt.GetMethod(), reqString[0]);
}

// TEST(RouterFunctionsTest, ProcessRouteTest) {
//     Router routerTest;
//     Request requestIt("d");
//     boost::asio::io_context io_context_;
//     ConnectionPtr userConnection = new Connection(io_context_, routerTest);
//     routerTest.processRoute(requestIt.command, userConnection);
// }

// TEST(RouterFunctionsTest, IsIWorkWithDataInterfaceWork) {
//     Router routerTest;
//     Request requestIt("d");

//     boost::asio::io_context io_context_;
//     ConnectionPtr userConnection = new Connection(io_context_, routerTest);

//     EXPECT_EQ(routerTest.GetWorkWithData()->operationWithData(requestIt.command, true), "a");
// }

// TEST(RouterFunctionsTest, IsProjectCreated) {
//     std::string path1 = "./test";
//     Router routerTest(path1);
//     std::string path2 = routerTest.GetProject()->GetPath();
//     EXPECT_EQ(path1, path2);
// }

// TEST(RouterFunctionsTest, SendToUsersTest) {
//     Router routerTest;
//     boost::asio::io_context io_context_;

//     ConnectionPtr userConnection = new Connection(io_context_, routerTest);
//     ConnectionPtr userConnection1 = new Connection(io_context_, routerTest);
//     Reply replyIt("d");
//     routerTest.GetProject()->ConnectUser(userConnection);
//     routerTest.GetProject()->ConnectUser(userConnection1);

//     EXPECT_EQ(routerTest.sendToUser(replyIt, userConnection), true);
//     EXPECT_EQ(routerTest.sendToAllProjectUsers(replyIt, userConnection), true);
// }

// /*boost::shared_ptr<IConnection> connectionPtr1 =
//         boost::shared_ptr<IConnection>();*/

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

// TEST(ProjectConnectTests, AttachExistingConnection) {
//     Router routerTest;
//     boost::asio::io_context io_context_;
//     Project projectTest;
//     // connectionIdCounter = 0, projectConnections is empty
//     ConnectionPtr userConnection = new Connection(io_context_, routerTest);
//     projectTest.ConnectUser(userConnection);

//     EXPECT_NE(projectTest.ConnectUser(userConnection), true);
//     EXPECT_EQ(projectTest.GetCounter(), 1);
// }

// TEST(ProjectConnectTests, AttachMultipleConnections) {
//     Router routerTest;
//     boost::asio::io_context io_context_;
//     Project projectTest;
//     // connectionIdCounter = 0, projectConnections is empty
//     ConnectionPtr userConnection1 = new Connection(io_context_, routerTest);
//     ConnectionPtr userConnection2 = new Connection(io_context_, routerTest);

//     projectTest.ConnectUser(userConnection1);
//     EXPECT_EQ(projectTest.ConnectionExist(userConnection1), true);
//     EXPECT_EQ(projectTest.GetCounter(), 1);
//     EXPECT_EQ(projectTest.FindConnectionId(userConnection1), 0);

//     EXPECT_NE(userConnection1, userConnection2);

//     EXPECT_EQ(projectTest.ConnectUser(userConnection2), true);
//     EXPECT_EQ(projectTest.GetCounter(), 2);
//     EXPECT_EQ(projectTest.FindConnectionId(userConnection2), 1);
// }

// TEST(ProjectDisonnectTests, DisconnectExistingConnection) {
//     Router routerTest;
//     boost::asio::io_context io_context_;
//     Project projectTest;
//     // connectionIdCounter = 0, projectConnections is empty
//     ConnectionPtr userConnection = new Connection(io_context_, routerTest);
//     projectTest.ConnectUser(userConnection);

//     EXPECT_EQ(projectTest.ConnectionExist(userConnection), true);
//     EXPECT_EQ(projectTest.GetCounter(), 1);
//     EXPECT_EQ(projectTest.FindConnectionId(userConnection), 0);

//     projectTest.DisconnectUser(userConnection);

//     EXPECT_NE(projectTest.ConnectionExist(userConnection), true);
//     EXPECT_EQ(projectTest.GetCounter(), 1);
//     EXPECT_EQ(projectTest.ConnectionExist(userConnection), false);
// }

// TEST(ProjectDisonnectTests, DisconnectNonExistingConnection) {
//     Router routerTest;
//     boost::asio::io_context io_context_;
//     Project projectTest;
//     // connectionIdCounter = 0, projectConnections is empty
//     ConnectionPtr userConnection = new Connection(io_context_, routerTest);

//     EXPECT_EQ(projectTest.DisconnectUser(userConnection), false);
//     EXPECT_EQ(projectTest.GetCounter(), 0);
//     EXPECT_EQ(projectTest.ConnectionExist(userConnection), false);
// }

// TEST(ProjectDisonnectTests, DisconnectMultipleConnections) {
//     Router routerTest;
//     boost::asio::io_context io_context_;
//     Project projectTest;
//     // connectionIdCounter = 0, projectConnections is empty
//     ConnectionPtr userConnection1 = new Connection(io_context_, routerTest);
//     ConnectionPtr userConnection2 = new Connection(io_context_, routerTest);

//     projectTest.ConnectUser(userConnection1);
//     projectTest.ConnectUser(userConnection2);
//     EXPECT_EQ(projectTest.GetProjectConnections().size(), 2);
//     EXPECT_EQ(projectTest.GetCounter(), 2);

//     projectTest.DisconnectUser(userConnection1);

//     EXPECT_EQ(projectTest.GetProjectConnections().size(), 1);
//     EXPECT_EQ(projectTest.GetCounter(), 2);
//     EXPECT_EQ(projectTest.ConnectionExist(userConnection1), false);
//     EXPECT_EQ(projectTest.ConnectionExist(userConnection2), true);

//     projectTest.DisconnectUser(userConnection2);

//     EXPECT_EQ(projectTest.GetProjectConnections().size(), 0);
//     EXPECT_EQ(projectTest.GetCounter(), 2);
//     EXPECT_EQ(projectTest.ConnectionExist(userConnection2), false);
// };

// class MockRouter : public IRouter {
//    public:
//     MOCK_METHOD(void, processRoute, (Request & request, const ConnectionPtr& userConnection), (override));

//     MOCK_METHOD2(sendToUser, bool(const Reply& reply, const ConnectionPtr& userConnection));

//     MOCK_METHOD(bool, sendToAllProjectUsers, (const Reply& reply, const ConnectionPtr& userConnection),
//                 (override));
// };

// TEST(GMockTests, RouterGMock) {
//     MockRouter mockRouter;
//     Reply replyIt("i");
//     Request requestIt("d");
//     ConnectionPtr connectionPtr{};
//     EXPECT_CALL(mockRouter, sendToUser(replyIt, connectionPtr)).Times(1);
//     EXPECT_CALL(mockRouter, processRoute(requestIt, connectionPtr)).Times(1);

//     mockRouter.sendToUser(replyIt, connectionPtr);
//     mockRouter.processRoute(requestIt, connectionPtr);
// }
