#include <iostream>
#include <boost/array.hpp>
#include "includes.hpp"

using namespace std;
int main() {
    Parser mypars;

    std::vector<ConnectionPtr> _connections;
    User tim("1");
    std::vector<User>  _users;
    _users.push_back(tim);

    Router rout(mypars, _connections, _users, "ttt");

    rout.getPrivat();

    cout << std::endl << "hi "  << std::endl;
    
    return 0;
}
