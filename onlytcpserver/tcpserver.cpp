#include "tcpserver.h"
#include <iostream>
#include <QtNetwork>
#include <QDebug>

using namespace std;


TcpServer::TcpServer(QObject *parent) : QObject(parent), qTcpServer(0)
{
    qTcpServer = new QTcpServer(this);
    connect(qTcpServer, SIGNAL(newConnection()),this, SLOT(acceptConnection()));
    qTcpServer->listen(QHostAddress::Any, 51345);
}

void TcpServer::acceptConnection()
{
    qTcpSocket = qTcpServer->nextPendingConnection();
    qTcpSocket->waitForReadyRead(0);

    string ipAddressPeer = qTcpSocket->peerAddress().toString().toStdString();
    cout << "Connected: " << ipAddressPeer;

    connect(qTcpSocket, SIGNAL(readyRead()),this, SLOT(startRead()));
    connect(qTcpSocket, SIGNAL(disconnected()),this,SLOT(disconnected()));

    //writeSomething();
}

void TcpServer::startRead()
{
    QTcpSocket *socketFromSender =static_cast<QTcpSocket*>(sender());
    QByteArray readContent = socketFromSender->readAll();
    qDebug() << readContent;
    socketFromSender->write(readContent);
    //QByteArray readContent = socketFromSender->readAll();
    //string contentString = readContent.constData();
    //cout << contentString;

    //socketFromSender->write(QString("OHYEAH BITCH").toUtf8());

}

void TcpServer::writeSomething(string textToSend)
{
    string test;
    cout << "Write something: ";
    cin >> test;
    QByteArray testByteArary(test.c_str() + "\n\r",test.length());
    qTcpSocket->write(testByteArary);

}

void TcpServer::disconnected()
{
    qTcpSocket->close();
}

TcpServer::~TcpServer()
{
    delete qTcpSocket;
    qTcpServer->close();
}
