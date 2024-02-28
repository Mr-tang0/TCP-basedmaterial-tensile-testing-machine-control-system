#include "tcpclient.h"


QTcpSocket *tcpClient::mySocket = new QTcpSocket;

tcpClient::tcpClient(QObject *parent)
    : QObject{parent}
{

}

QStringList tcpClient::getNetWorkIP()
{
    QStringList IPList;
    foreach (QHostAddress localAddress, QNetworkInterface::allAddresses()) {
        if(localAddress.protocol()==QAbstractSocket::IPv4Protocol)
        IPList.append(localAddress.toString());
    }
    return IPList;
}
bool tcpClient::tcpConnect(QString IPAddress, int portNumber)
{
    mySocket->connectToHost(QHostAddress(IPAddress),portNumber);
    connect(mySocket,&QTcpSocket::connected,[=](){
        qDebug()<<"connected!";
        emit connected();
    });
    connect(mySocket,&QTcpSocket::disconnected,[=](){
        qDebug()<<"disconnected!";
        emit disconnected();
    });
    connect(mySocket,&QTcpSocket::readyRead,[=](){
        QByteArray message = mySocket->readLine();
        emit readSomeMessage(message);
    });
}

bool tcpClient::sendMessage(QByteArray message)
{
    if(mySocket->isOpen())
    {
        bool flag  = mySocket->write(message);
        qDebug()<<flag;
        return flag;
    }
    else {
        emit disconnected();
        return false;
    }

}
