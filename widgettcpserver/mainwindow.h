#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpserver.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void updateText(QByteArray &readContant);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TcpServer *tcpserver;

private slots:

void on_listenButton_clicked();
void on_sendTextButton_clicked();
void on_disconnectButton_clicked();
void on_stopListenButton_clicked();
};

#endif // MAINWINDOW_H
