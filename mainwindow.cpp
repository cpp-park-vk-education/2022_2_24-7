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
//    client->addFunc(this->serverAsked);
    client->addClass(this);
    ui->setupUi(this);

    newThread = new mythread(context, client, this);
    newThread->start();

    editor.userFirst(1);

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
   nlohmann::json j = nlohmann::json::parse(serverString);
   std::string command = j["command"].get<std::string>();
   if (id_ == 0) {
       id_ = j["id"].get<int>();
   }

   isCommandBefore = true;

   QString operation = QString::fromStdString(command);

   operation = QString::fromStdString(editor.operationWithData(operation.toStdString(), 1));

   if (operation.split(':')[0] == 'i') {
       insertIntoPosition(operation.split(':')[2].toInt(), operation.split(':')[1][0]);
   } else if (operation.split(':')[0] == 'd') {
       deleteFromPosition(operation.split(':')[1].toULongLong());
   }
}

void MainWindow::contextRun() { context.run(); }

void MainWindow::sockDisc(){
}

void MainWindow::sockReady() {
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QString texto = ui->idProjectLabel->text();
    texto += char(e->key());
    ui->idProjectLabel->setText(texto);
}


void MainWindow::on_connectProjectButton_clicked()
{
//    this->nameProject = ui->idProject->toPlainText();
//    ui->idProjectLabel->setText(nameProject);
//    MainWindow* a = this;
//    client->addFunc(&a->serverAsked);
//    client->addClass(a);
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
    bool flag = false;
    if (sym.length() > this->curLengt) {
            insertSym();
            flag = true;
    } else
    if (sym.length() < this->curLengt) {
        deleteSym();
        flag = true;
    }
    qDebug() << dataForManager;
    if (flag && !(dataForManager.split(':')[0] == 'd' && dataForManager.split(':')[1].toInt() < 0) && !isCommandBefore) {
        std::string command = editor.operationWithData(dataForManager.toStdString());
        qDebug() << QString::fromStdString(command);
        client->sendMsg(command);
        isCommandBefore = false;
    }

    dataForManager.clear();
//    curSym = this->sym[this->sym.length()-1];
}

size_t MainWindow::insertIntoPosition(int position, QChar insertedSymb) {
    int positionBeforeChanges = ui->codeText->textCursor().position();
    int returnPositionCursor = positionBeforeChanges;

    textCursor.setPosition(position,QTextCursor::MoveAnchor);

    textCursor.insertText(insertedSymb);

    if(position <= positionBeforeChanges) {
        returnPositionCursor = positionBeforeChanges + 1;
    }

    textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, returnPositionCursor);

    return returnPositionCursor;
};

size_t MainWindow::deleteFromPosition(size_t position) {
    int positionBeforeChanges = ui->codeText->textCursor().position();
    int returnPositionCursor = positionBeforeChanges;

    textCursor = ui->codeText->textCursor();
    textCursor.setPosition(position,QTextCursor::MoveAnchor);

    textCursor.deleteChar();



    if(position <= positionBeforeChanges) {
        returnPositionCursor = positionBeforeChanges - 1;
    }

    textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, returnPositionCursor);

    return returnPositionCursor;
};

