#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <string.h>

class Server
{

public:

    Server(boost::asio::io_service, boost::asio::ip::tcp::endpoint); // здесь должны создвться хендлеры
    void start();
    void stop();

private:

    boost::asio::io_service IOCervice_;
    boost::asio::ip::tcp::acceptor Ccceptor_;
    Router<std::string(*)(const std::string &)> RequestRouter;
    std::vector<Connection*> Connections_;
};


class Connection
{

public:

    Connection(Server*, boost::asio::ip::tcp::socket);
    void start();
    void stop();

private:

    Server* Server_;
    boost::asio::ip::tcp::socket Socet_;

    static const int MaxMsg = 1024;

    char WriteBuf[MaxMsg];
    char ReadBuf[MaxMsg];
    
    void onRead();
    void onWrite();
    void doRead();
    void doWrite();

    ParserSerializer Parser;
};

template<typename Heandler>
class Router
{

public:

    void AddHeandler(std::string, Heandler);
    std::string processRoute(std::string, std::string);

private:

    std::unordered_map<std::string, Heandler> Handlers;

};


class ParserSerializer
{

public:

    std::string Parse(std::string);
    std::string Serialize(std::string);

};