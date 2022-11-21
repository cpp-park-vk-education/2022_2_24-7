#include <vector>
#include <string>
#include <chat.hpp>

using namespace std;

class Chat {
    bool createChatFile(string path){
		path = "";
		return true;
	}; 

    public:
        Chat(string dir): chatDir(dir){};

        bool wrightMessage(string msg){ 
			msg = "";
			return true; };

        string getWholeChat(){return "true"; };

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

        bool addUser(int Id, string name = "1"){
			Id = 1;
            createChat(name);
			return Id;
        };

        bool deleteUser(int Id){ 
			Id = 1;
			return Id; };

        bool createChat(string name){
			name = "";
			return true; };

        bool getMessageToChat(string msg){
			msg = "";
			return true; };

        bool sendMessageToChatUsers(string msg){ 
			msg = "";
			return true; };

    private:
        int id;
        Chat chat = Chat("1");
        vector<User> users;
};
