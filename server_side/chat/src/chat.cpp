#include <vector>
#include <string>
using namespace std;

class Chat {
    bool createChatFile(string){}; 

    public:
        Chat(string dir): chatDir(dir){};

        bool wrightMessage(string){};

        string getWholeChat(){};

    private:
        string chatDir;
};

class User {
    public:
        int id;

        string name;

        User(int ID): id(ID){};
};

class Project {
    public:
        Project(int Id): id(Id){};

        bool addUser(string name, int Id){
            createChat("1");
        };

        bool deleteUser(int Id){};

        bool createChat(string){};

        bool getMessageToChat(string){};

        bool sendMessageToChatUsers(string){};

    private:
        int id;
        Chat chat = Chat("1");
        vector<User> users;
};