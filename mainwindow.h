#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QTextCursor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTcpSocket* socket;
    QByteArray Data;
    QTextCursor textCursor;
    QString sym;
    QString dataForManager;
    QString nameProject;

    QString curSym;
    int curLengt = 0;
    void insertSym();
    void deleteSym();


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
protected:
    void keyPressEvent(QKeyEvent *e);

};
#endif // MAINWINDOW_H
