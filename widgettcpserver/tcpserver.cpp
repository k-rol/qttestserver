#include "tcpserver.h"
#include <iostream>
#include <QtNetwork>
#include <QDebug>


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

    //writeSomething();
}

void TcpServer::startRead()
{
    /*
    QTcpSocket *socketFromSender =static_cast<QTcpSocket*>(sender());
    QByteArray readContent = socketFromSender->readAll();
    qDebug() << readContent;
    socketFromSender->write(readContent);
    */

    QByteArray readContent = qTcpSocket->readAll();
    qDebug() << readContent;

    qTcpSocket->write(readContent);

/*
    string stdString = "I am Very HAPPY!";
    QByteArray byteArray(stdString.c_str(), stdString.length());

    quint64 some64 = qTcpSocket->write(byteArray);
    qDebug() << some64;
*/
}

void TcpServer::writeSomething()
{
    /*qDebug() << "writeSomething()...";
    QByteArray testByteArary("oh yeeeeeah WORKING!");
    qTcpSocket->write(testByteArary);
    bool ok = qTcpSocket->flush();
    qDebug() << ok;*/

    string stdString = "I am Very HAPPY!";
    QByteArray byteArray(stdString.c_str(), stdString.length());

    quint64 some64 = qTcpSocket->write(byteArray);
    qDebug() << some64;

    bool ok = qTcpSocket->flush();
    qDebug() << ok;
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

