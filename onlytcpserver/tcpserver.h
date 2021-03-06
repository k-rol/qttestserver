#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>


class QTcpServer;
class QTcpSocket;



class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = 0);
    virtual ~TcpServer();

private slots:
    void acceptConnection();
    void startRead();
    void disconnected();
    void writeSomething();

private:
    QTcpServer *qTcpServer;
    QTcpSocket *qTcpSocket;


};

#endif // TCPSERVER_H
