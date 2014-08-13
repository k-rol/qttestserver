#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpserver.h"
#include <QDebug>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpserver = new TcpServer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listenButton_clicked()
{
    qDebug() << "THAT BITCH!";
    tcpserver->startService();

}

void MainWindow::on_sendTextButton_clicked()
{
    qDebug() << "Should send something...";
    /*QTcpSocket *socket = tcpserver->qTcpSocket;
    socket->write(QByteArray("Something Sent"));
    */
    tcpserver->writeSomething();
}
