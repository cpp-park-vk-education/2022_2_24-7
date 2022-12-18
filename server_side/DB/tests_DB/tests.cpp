#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "includes.hpp"

TEST(DefaultTestBack, Test) {
    EXPECT_EQ((2 * 2), 4);
}

TEST(BackendConstructorsTest, RouterTest) {
    Router routerTest;
}

TEST(BackendConstructorsTest, ProjectTest) {
    Project projectTest;
}

TEST(BackendConstructorsTest, UserTest) {
    boost::shared_ptr<IConnection> myConnectionPtr = boost::shared_ptr<IConnection>();
    User userTest(2, myConnectionPtr, 2);
    userTest.countUserChanges ++;

    EXPECT_EQ(userTest.userID, 2);
    EXPECT_EQ(userTest.countUserChanges, 3);
}

TEST(RouterFunctionsTest, AddHandlerTest) {
    Router routerTest;
    EXPECT_EQ(routerTest.addHandler("i", InsertSymbol), true);
    EXPECT_EQ(routerTest.GetHandlers().size(), 1);

    EXPECT_EQ(routerTest.addHandler("d", DeleteSymbol), true);
    EXPECT_NE(routerTest.GetHandlers().size(), 1);
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
    boost::shared_ptr<IConnection> myConnectionPtr = boost::shared_ptr<IConnection>();
    EXPECT_EQ(routerTest.processRoute(requestIt, myConnectionPtr), true);
}


TEST(RouterFunctionsTest, CreateProjectTest) {
    Router routerTest;
    std::string path1 = "./test";
    EXPECT_EQ(routerTest.createProject(path1), true);
    std::string path2 = routerTest.GetProject().GetPath();
    EXPECT_EQ(path1, path2);
}

TEST(RouterFunctionsTest, SendTest) {
    Router routerTest;
    boost::shared_ptr<IConnection> myConnectionPtr = boost::shared_ptr<IConnection>();
    Reply replyIt("d");
    EXPECT_EQ(routerTest.sendToUser(replyIt, myConnectionPtr), true);
    EXPECT_EQ(routerTest.sendToAllProjectUsers(replyIt, myConnectionPtr), true);
}

TEST(ProjectFunctionsTest, GettersTest) {
    Project projectTest;
    EXPECT_EQ(projectTest.GetName(), "project");
    EXPECT_EQ(projectTest.GetUsers().size(), 0);
    EXPECT_EQ(projectTest.GetPath(), "./files");
    EXPECT_EQ(projectTest.GetCounter(), 0);
}


TEST(ProjectFunctionsTest, UserTest) {
    Project projectTest;
    boost::shared_ptr<IConnection> myConnectionPtr1 = boost::shared_ptr<IConnection>();
    
    projectTest.ConnectUser(myConnectionPtr1);
    EXPECT_EQ(projectTest.GetUsers().size(), 1);
    EXPECT_EQ(projectTest.GetCounter(), 1);

    projectTest.ConnectUser(myConnectionPtr1);
    EXPECT_NE(projectTest.GetUsers().size(), 2);
    EXPECT_NE(projectTest.GetCounter(), 2);

    projectTest.DisconnectUser(myConnectionPtr1);
    EXPECT_EQ(projectTest.GetUsers().size(), 0);
    EXPECT_EQ(projectTest.GetCounter(), 1);

    projectTest.ConnectUser(myConnectionPtr1);
    EXPECT_EQ(projectTest.GetUsers().size(), 1);
    EXPECT_EQ(projectTest.GetCounter(), 2);
}

TEST(HandlersTest, InsertTest) {
    Request requestIt("d");
    std::string filePath = "./files";
    Reply replyIt("d");
    EXPECT_EQ(replyIt.command, InsertSymbol(requestIt, filePath).command);
}

TEST(HandlersTest, DeleteTest) {
    Request requestIt("d");
    std::string filePath = "./files";
    Reply replyIt("d");
    EXPECT_EQ(replyIt.GetMethod(), DeleteSymbol(requestIt, filePath).GetMethod());
}

class MockRouter : public IRouter {
public:
    MOCK_METHOD(
        bool,
        addHandler,
        (const std::string& method, const Handler& handler),
        (override)
    );

    MOCK_METHOD(
        bool,
        processRoute,
        (const Request &request, const ConnectionPtr &userConnection),
        (override)
    );

    MOCK_METHOD(
        bool,
        sendToUser,
        (const Reply &reply, const ConnectionPtr& userConnection),
        (override)
    );

    MOCK_METHOD(
        bool,
        sendToAllProjectUsers,
        (const Reply &reply, const ConnectionPtr& userConnection),
        (override)
    );
};

TEST(GMockTests, RouterGMock) {
    MockRouter mockRouter;
    Reply replyIt("i");
    Request requestIt("d");
    ConnectionPtr myConnectionPtr{};
    EXPECT_CALL(mockRouter, sendToUser(replyIt, myConnectionPtr)).Times(1);
    EXPECT_CALL(mockRouter, addHandler("i", InsertSymbol)).Times(1);
    EXPECT_CALL(mockRouter, processRoute(requestIt, myConnectionPtr)).Times(1);

    mockRouter.sendToUser(replyIt, myConnectionPtr);
    mockRouter.addHandler("i", InsertSymbol);
    mockRouter.processRoute(requestIt, myConnectionPtr);
}
