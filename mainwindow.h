#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QTextCursor>
#include "./ui_mainwindow.h"

#include "WorkWithData.hpp"
#include "Client.hpp"
#include "nlohmann/json.hpp"
#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QByteArray Data;
    QTextCursor textCursor;
    QString sym;
    QString dataForManager;
    QString nameProject;

    WorkWithData editor;

    QString curSym;
    int curLengt = 0;
    void insertSym();
    void deleteSym();
    void contextRun();

    void serverAsked(std::string) override;

public slots:
    void sockReady();
    void sockDisc();

private slots:

    void on_connectProjectButton_clicked();

    void on_createProjectButton_clicked();

    void on_codeText_cursorPositionChanged();

    void on_codeText_textChanged();

private:

    Ui::MainWindow *ui;
    int id_ = 0;
    bool isCommandBefore = false;

    size_t insertIntoPosition(int position, QChar insertedSymb);
    size_t deleteFromPosition(size_t position);
protected:
    void keyPressEvent(QKeyEvent *e);

    boost::asio::io_context context;
    std::shared_ptr<Client> client;

    mythread* newThread;

};
#endif // MAINWINDOW_H
