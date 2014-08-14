#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpserver.h"
#include <QDebug>
#include <QTcpSocket>

using namespace std;

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

void MainWindow::updateText(QByteArray &readContent)
{
    QString textToAdd = QString(readContent);

    if (textToAdd.endsWith("\n"))
    {
        textToAdd.remove(textToAdd.length()-1,1);
    }
    else if (textToAdd.endsWith("\r\n") || textToAdd.endsWith("\n\r"))
    {
        textToAdd.remove(textToAdd.length()-2,2);
    }

    ui->chatTextbox->appendPlainText(textToAdd.trimmed());
}

void MainWindow::on_listenButton_clicked()
{
    qDebug() << "THAT BITCH!";
    tcpserver->startService();
    ui->chatTextbox->appendPlainText("Listening to port 51345 ...");

}

void MainWindow::on_sendTextButton_clicked()
{
    string nickName = "" + ui->nickTextBox->text().toStdString() + "> ";
    string textToSend = ui->sendTextBox->text().toStdString() + "\n";
    string wholeText = nickName+textToSend;
    tcpserver->writeSomething(wholeText);

    QString textToAdd = wholeText.c_str();

    if (textToAdd.endsWith("\n") || textToAdd.endsWith("\r\n"))
    {
        textToAdd.remove(textToAdd.length()-1,1);
    }

    ui->chatTextbox->appendPlainText(textToAdd.trimmed());
//

}

void MainWindow::on_disconnectButton_clicked()
{
    tcpserver->disconnectIt();
}

void MainWindow::on_stopListenButton_clicked()
{
    tcpserver->stopListening();
}
