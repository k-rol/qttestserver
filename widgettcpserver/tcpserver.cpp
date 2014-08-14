#include "tcpserver.h"
#include <iostream>
#include <QtNetwork>
#include <QDebug>
#include <ui_mainwindow.h>
#include <mainwindow.h>

using namespace std;


TcpServer::TcpServer(QObject *parent) : QObject(parent), qTcpServer(0)
{
    qDebug() << "TcpServer instance created.";
}

void TcpServer::startService()
{
    qTcpServer = new QTcpServer(this);
    connect(qTcpServer, SIGNAL(newConnection()),this, SLOT(acceptConnection()));
    qTcpServer->listen(QHostAddress::Any, 51345);
    qDebug() << "Listening to port 51345 ...";
}

void TcpServer::acceptConnection()
{
    qTcpSocket = qTcpServer->nextPendingConnection();
    qTcpSocket->waitForReadyRead(0);

    string ipAddressPeer = qTcpSocket->peerAddress().toString().toStdString();
    cout << "Connected: " << ipAddressPeer;

    connect(qTcpSocket, SIGNAL(readyRead()),this, SLOT(startRead()));
    connect(qTcpSocket, SIGNAL(disconnected()),this,SLOT(disconnected()));
    //connect(qTcpSocket, SIGNAL(aboutToClose()),this, SLOT(aboutToDisconnect());

}

void TcpServer::startRead()
{

    QByteArray readContent = qTcpSocket->readAll();
    qDebug() << readContent;

    MainWindow *instanceMainWindow = static_cast<MainWindow*>(this->parent());
    instanceMainWindow->updateText(readContent);

}

void TcpServer::nothingreally()
{
    qDebug() << "NothingReally...";
}

void TcpServer::writeSomething(string textToSend)
{
    QByteArray byteArray(textToSend.c_str(),textToSend.length());
    qTcpSocket->write(byteArray);
}

//Stops listening when button is pressed
void TcpServer::stopListening()
{
    if (qTcpServer->isListening())
    {
        qTcpServer->close();
    }
}

//Disconnect current connection
void TcpServer::disconnectIt()
{
    if (qTcpSocket->isOpen())
    {
        writeSomething("CMD DISCONNECT");
        qTcpSocket->close();
    }
}

void TcpServer::disconnected()
{
    qTcpSocket->close();
}

TcpServer::~TcpServer()
{
//    delete qTcpSocket;
//    qTcpServer->close();
    qDebug() << "TcpServer instance deleted";
}

