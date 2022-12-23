#include "Dto.hpp"

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

#include <string>
#include <vector>

class Client {
   public:
    Client(boost::asio::io_context& context, std::string ip, unsigned int port);
    ~Client() {}

    void sendData();
    void getData();
    void setDto(std::string command);
    void connect();
    void stopConnection();
    bool isCommandStop() { return dto.command == "STOP"; }

   private:
    boost::asio::posix::stream_descriptor _inputStream;
    boost::asio::ip::tcp::socket _socket;

    std::string _ip = "127.0.0.1";
    unsigned int _port = 80;

    Dto dto;
};
