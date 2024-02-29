#include "tcpclient.h"


QTcpSocket *tcpClient::mySocket = new QTcpSocket;


tcpClient::tcpClient(QObject *parent)
    : QObject{parent}
{

    connect(timer,&QTimer::timeout,this,[=](){
        QByteArray message = mySocket->readAll();
        readBuffer = readBuffer + message;
        if(readBuffer.length()>=218)
        {
            emit readSomeMessage(messageToTrame(readBuffer.mid(0,218)));
            readBuffer.clear();
        }
    });

}

bool tcpClient::isopen()
{
    return mySocket->isOpen();
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
bool tcpClient::tcpConnect()
{
    QString IPAddress = details.netWorkIP;
    int portNumber = details.portNumber;

    mySocket->connectToHost(QHostAddress(IPAddress),portNumber);
    connect(mySocket,&QTcpSocket::connected,this, [=](){
        qDebug()<<"connected!";
        timer->start(1000/details.sampleRate);
        emit connected();
    });
    connect(mySocket,&QTcpSocket::disconnected,this,[=](){
        qDebug()<<"disconnected!";
        timer->stop();
        emit disconnected();
    });


    return mySocket->isOpen();
}

bool tcpClient::sendMessage(QByteArray message)
{
    if(mySocket->isOpen())
    {
        bool flag  = mySocket->write(message);
        return flag;
    }
    else {
        emit disconnected();
        return false;
    }

}

TCPFrame tcpClient::messageToTrame(QByteArray message)
{
    TCPFrame tempFrame;
    tempFrame.header = message.mid(0,10);
    tempFrame.tail = message.right(4);

    for(int i = 0;i<51;i++)
    {
        tempFrame.data.append(message.mid(10+4*i,4));
    }

    return tempFrame;
}

