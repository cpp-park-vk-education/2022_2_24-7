#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "includes.hpp"

TEST(BackendConstructorsTest, RouterConstructorTest) {
    Router routerTest;
    EXPECT_EQ(routerTest.GetProject()->GetPath(), "./files");
    EXPECT_NE(routerTest.GetWorkWithData(), nullptr);
}

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

TEST(RouterFunctionsTest, ProcessRouteTest) {
    Router routerTest;
    Request requestIt("d");
    ConnectionPtr userConnection = std::make_shared<Connection>();
    routerTest.processRoute(requestIt, userConnection);
}

TEST(RouterFunctionsTest, IsIWorkWithDataInterfaceWork) {
    Router routerTest;
    Request requestIt("d");
    ConnectionPtr userConnection = std::make_shared<Connection>();

    EXPECT_EQ(routerTest.GetWorkWithData()->operationWithData(requestIt.command, true), "a");
}

TEST(RouterFunctionsTest, IsProjectCreated) {
    std::string path1 = "./test";
    Router routerTest(path1);
    std::string path2 = routerTest.GetProject()->GetPath();
    EXPECT_EQ(path1, path2);
}

TEST(RouterFunctionsTest, SendToUsersTest) {
    Router routerTest;
    ConnectionPtr userConnection = std::make_shared<Connection>(1);
    ConnectionPtr userConnection1 = std::make_shared<Connection>(2);
    Reply replyIt("d");
    routerTest.GetProject()->ConnectUser(userConnection);
    routerTest.GetProject()->ConnectUser(userConnection1);

    EXPECT_EQ(routerTest.sendToUser(replyIt, userConnection), true);
    EXPECT_EQ(routerTest.sendToAllProjectUsers(replyIt, userConnection), true);
}

/*boost::shared_ptr<IConnection> connectionPtr1 =
        boost::shared_ptr<IConnection>();*/

TEST(ProjectConnectTests, AttachNewConnection) {
    Project projectTest;
    // connectionIdCounter = 0, projectConnections is empty
    ConnectionPtr userConnection = std::make_shared<Connection>();
    projectTest.ConnectUser(userConnection);

    EXPECT_EQ(projectTest.ConnectionExist(userConnection), true);
    EXPECT_EQ(projectTest.GetCounter(), 1);
    EXPECT_EQ(projectTest.FindConnectionId(userConnection), 0);
    EXPECT_EQ(projectTest.GetProjectConnections().size(), 1);
}

TEST(ProjectConnectTests, AttachExistingConnection) {
    Project projectTest;
    // connectionIdCounter = 0, projectConnections is empty
    ConnectionPtr userConnection = std::make_shared<Connection>();
    projectTest.ConnectUser(userConnection);

    EXPECT_NE(projectTest.ConnectUser(userConnection), true);
    EXPECT_EQ(projectTest.GetCounter(), 1);
}

TEST(ProjectConnectTests, AttachMultipleConnections) {
    Project projectTest;
    // connectionIdCounter = 0, projectConnections is empty
    ConnectionPtr userConnection1 = std::make_shared<Connection>(1);
    ConnectionPtr userConnection2 = std::make_shared<Connection>(2);

    projectTest.ConnectUser(userConnection1);
    EXPECT_EQ(projectTest.ConnectionExist(userConnection1), true);
    EXPECT_EQ(projectTest.GetCounter(), 1);
    EXPECT_EQ(projectTest.FindConnectionId(userConnection1), 0);

    EXPECT_NE(userConnection1, userConnection2);

    EXPECT_EQ(projectTest.ConnectUser(userConnection2), true);
    EXPECT_EQ(projectTest.GetCounter(), 2);
    EXPECT_EQ(projectTest.FindConnectionId(userConnection2), 1);
}

TEST(ProjectDisonnectTests, DisconnectExistingConnection) {
    Project projectTest;
    // connectionIdCounter = 0, projectConnections is empty
    ConnectionPtr userConnection = std::make_shared<Connection>();
    projectTest.ConnectUser(userConnection);

    EXPECT_EQ(projectTest.ConnectionExist(userConnection), true);
    EXPECT_EQ(projectTest.GetCounter(), 1);
    EXPECT_EQ(projectTest.FindConnectionId(userConnection), 0);

    projectTest.DisconnectUser(userConnection);

    EXPECT_NE(projectTest.ConnectionExist(userConnection), true);
    EXPECT_EQ(projectTest.GetCounter(), 1);
    EXPECT_EQ(projectTest.ConnectionExist(userConnection), false);
}

TEST(ProjectDisonnectTests, DisconnectNonExistingConnection) {
    Project projectTest;
    // connectionIdCounter = 0, projectConnections is empty
    ConnectionPtr userConnection = std::make_shared<Connection>();

    EXPECT_EQ(projectTest.DisconnectUser(userConnection), false);
    EXPECT_EQ(projectTest.GetCounter(), 0);
    EXPECT_EQ(projectTest.ConnectionExist(userConnection), false);
}

TEST(ProjectDisonnectTests, DisconnectMultipleConnections) {
    Project projectTest;
    // connectionIdCounter = 0, projectConnections is empty
    ConnectionPtr userConnection1 = std::make_shared<Connection>(1);
    ConnectionPtr userConnection2 = std::make_shared<Connection>(2);

    projectTest.ConnectUser(userConnection1);
    projectTest.ConnectUser(userConnection2);
    EXPECT_EQ(projectTest.GetProjectConnections().size(), 2);
    EXPECT_EQ(projectTest.GetCounter(), 2);

    projectTest.DisconnectUser(userConnection1);

    EXPECT_EQ(projectTest.GetProjectConnections().size(), 1);
    EXPECT_EQ(projectTest.GetCounter(), 2);
    EXPECT_EQ(projectTest.ConnectionExist(userConnection1), false);
    EXPECT_EQ(projectTest.ConnectionExist(userConnection2), true);

    projectTest.DisconnectUser(userConnection2);

    EXPECT_EQ(projectTest.GetProjectConnections().size(), 0);
    EXPECT_EQ(projectTest.GetCounter(), 2);
    EXPECT_EQ(projectTest.ConnectionExist(userConnection2), false);
};

class MockRouter : public IRouter {
   public:
    MOCK_METHOD(void, processRoute, (Request & request, const ConnectionPtr& userConnection), (override));

    MOCK_METHOD2(sendToUser, bool(const Reply& reply, const ConnectionPtr& userConnection));

    MOCK_METHOD(bool, sendToAllProjectUsers, (const Reply& reply, const ConnectionPtr& userConnection),
                (override));
};

TEST(GMockTests, RouterGMock) {
    MockRouter mockRouter;
    Reply replyIt("i");
    Request requestIt("d");
    ConnectionPtr connectionPtr{};
    EXPECT_CALL(mockRouter, sendToUser(replyIt, connectionPtr)).Times(1);
    EXPECT_CALL(mockRouter, processRoute(requestIt, connectionPtr)).Times(1);

    mockRouter.sendToUser(replyIt, connectionPtr);
    mockRouter.processRoute(requestIt, connectionPtr);
}
