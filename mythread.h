#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QApplication>
#include "Client.hpp"

class mythread : public QThread
{
    Q_OBJECT
public:
    explicit mythread(boost::asio::io_context& context, std::shared_ptr<Client>& a, QObject *parent = nullptr) : _client(a), _context(context) {}
    void run();

signals:
    void stringFromServer(std::string);

private:
    std::shared_ptr<Client> _client;
    boost::asio::io_context& _context;
};

#endif
