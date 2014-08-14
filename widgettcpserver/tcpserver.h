#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>

using namespace std;

class QTcpServer;
class QTcpSocket;

class MainWindow;

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = 0);
    void startService();
    void writeSomething(string textToSend);
    void disconnectIt();
    void stopListening();
    virtual ~TcpServer();

private slots:
    void acceptConnection();
    void startRead();
    void disconnected();
    void nothingreally();

private:
    QTcpServer *qTcpServer;
    QTcpSocket *qTcpSocket;

    MainWindow *mainWindow;
};

#endif // TCPSERVER_H
