#include "mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , context()
{
    client = std::make_shared<Client>(context);
    ui->setupUi(this);

    editor.userFirst(0,0);

    newThread = new mythread(context, client, this);
    newThread->start();

//    connect(threadNew, SIGNAL(stringFromServer(std::string)), this, SLOT(serverAsked(std::string)));
//    client->start();

//    contextRun();
//    std::thread t(&MainWindow::server_threads_spawn, this);
//    t.join();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serverAsked(std::string serverString) {
//    nlohmann::json j = nlohmann::json::parse(serverString);
//    std::string command = j["command"].get<std::string>();
//    if (id_ == 0) {
//        id_ = j["id"].get<int>();
//        editor.userFirst(id_);
//    }

//    isCommandBefore = true;

//    QString operation = QString::fromStdString(command);

//    operation = QString::fromStdString(editor.operationWithData(operation.toStdString(), 1));

//    if (ui->commandLine->text().split(':')[0] == 'i') {
//        insertIntoPosition(operation.split(':')[2].toInt(), operation.split(':')[1][0]);
//    } else {
//        deleteFromPosition(operation.split(':')[1].toULongLong());
//    }
}

void MainWindow::contextRun() { context.run(); }

void MainWindow::sockDisc(){
}

void MainWindow::sockReady() {
//    if (socket->waitForConnected(500)) {
//        socket->waitForReadyRead(500);
//        Data = socket->readAll();
//        qDebug() << Data;
//    }


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
    QChar a = ui->idProject->toPlainText()[0];
    insertIntoPosition(ui->idProject->toPlainText().toULongLong(),a);
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
    dataForManager.append(QString::number(textCursor.position()-1));
}

void MainWindow::deleteSym(){
    this->curLengt = this->sym.length();
    this->dataForManager.append("d:");
//    this->dataForManager.append(this->curSym);
//    dataForManager.append(':');
    dataForManager.append(QString::number(textCursor.position()));
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
        qDebug() << QString::fromStdString(editor.operationWithData(dataForManager.toStdString()));
        client->sendMsg(editor.operationWithData(dataForManager.toStdString()));
    //}
    dataForManager.clear();
    curSym = this->sym[this->sym.length()-1];
}

size_t MainWindow::insertIntoPosition(int position, QChar insertedSymb) {
    int positionBeforeChanges = ui->codeText->textCursor().position();
    int returnPositionCursor = positionBeforeChanges;

//    textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, -position);
    textCursor.setPosition(position,QTextCursor::MoveAnchor);

    textCursor.insertText(insertedSymb);

    if(position <= positionBeforeChanges) {
        returnPositionCursor = positionBeforeChanges + 1;
    }

    textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, returnPositionCursor);

    return returnPositionCursor;
};

size_t MainWindow::deleteFromPosition(size_t position) {
    size_t returnPositionCursor;
    size_t positionBeforeChanges = ui->codeText->textCursor().position();

    ui->codeText->textCursor().setPosition(position);
    ui->codeText->textCursor().deleteChar();

    if(position > positionBeforeChanges) {
        returnPositionCursor = positionBeforeChanges - 1;
    } else {
        returnPositionCursor = positionBeforeChanges;
    }

    ui->codeText->textCursor().setPosition(positionBeforeChanges);
    textCursor = ui->codeText->textCursor();

    return returnPositionCursor;
};
