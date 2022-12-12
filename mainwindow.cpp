#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

        socket->connectToHost("127.0.0.1",5555);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sockDisc(){
    socket->deleteLater();
}

void MainWindow::sockReady() {
    if (socket->waitForConnected(500)) {
        socket->waitForReadyRead(500);
        Data = socket->readAll();
        qDebug() << Data;
    }
}




void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QString texto = ui->idProjectLabel->text();
    texto += char(e->key());
    ui->idProjectLabel->setText(texto);
}


void MainWindow::on_connectProjectButton_clicked()
{
    this->nameProject = ui->idProject->toPlainText();
    ui->idProjectLabel->setText(nameProject);
}


void MainWindow::on_createProjectButton_clicked()
{

}


void MainWindow::on_codeText_cursorPositionChanged()
{
    this->textCursor = ui->codeText->textCursor();
}

void MainWindow::insertSym(){
    this->curLengt = this->sym.length();
    this->dataForManager.append("i:");
    this->dataForManager.append(sym.at(textCursor.position()-1));
    dataForManager.append(':');
    dataForManager.append(QString::number(textCursor.position()));
}

void MainWindow::deleteSym(){
    this->curLengt = this->sym.length();
    this->dataForManager.append("d:");
    this->dataForManager.append(this->curSym);
    dataForManager.append(':');
    dataForManager.append(QString::number(textCursor.position()+1));
}

void MainWindow::on_codeText_textChanged()
{
    this->sym = ui->codeText->toPlainText();

    if (sym.length() > this->curLengt) {
        insertSym();
    } else
    {
        deleteSym();
    }
    //if (sym.length() != 0) {
        //qDebug() << sym.at(textCursor.position()-1) << "    " << textCursor.position();
        qDebug() << dataForManager;
    //}
    dataForManager.clear();
    curSym = this->sym[this->sym.length()-1];
}

