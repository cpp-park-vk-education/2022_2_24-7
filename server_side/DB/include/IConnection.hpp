#pragma once

#include <boost/shared_ptr.hpp>


class IConnection {
   public:
    virtual void handle_read() = 0;
    virtual void handle_write() = 0;
    virtual void start() = 0;
    virtual void get_socket() = 0;
};

class Connection : public IConnection {
   public:
    Connection(int id = 0) { ID = id; };
    void handle_read() override{};
    void handle_write() override{};
    void start() override{};
    void get_socket() override{};
   private:
    int ID;
};
using ConnectionPtr = std::shared_ptr<IConnection>;
// это интерфейс сущности из сервера проекта, он служит для последующей
// интеграции
//using ConnectionPtr = IConnection *;
