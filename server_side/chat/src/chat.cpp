#include "chat.hpp"
#include <string>
#include <vector>

using namespace std;

class Chat {
    bool createChatFile(string path) {
        chatDir = path;
        return true;
    };

   public:
    Chat(string dir) { createChatFile(dir); };

    bool wrightMessage(string msg) {
        msg = "";
        return true;
    };

    string getWholeChat() { return "true"; };

    string getChatDir() { return chatDir; }

   private:
    string chatDir;
};

class User {
   public:
    int id;

    string name;

    User(int ID, string Name) : id(ID), name(Name){};
};

class Project {
   public:
    Project(int Id) : id(Id){};

    bool addUser(int Id, string name = "1") {
        Id = 1;
        createChat(name);
        return Id;
    };

    bool deleteUser(int Id) {
        Id = 1;
        return Id;
    };

    bool createChat(string name) {
        name = "";
        return true;
    };

    bool getMessageToChat(string msg) {
        msg = "";
        return true;
    };

    bool sendMessageToChatUsers(string msg) {
        msg = "";
        return true;
    };

    int getID() { return id; };

   private:
    int id;
    Chat chat = Chat("1");
    vector<User> users;
};
