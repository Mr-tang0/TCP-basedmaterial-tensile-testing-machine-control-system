#include "tcpclient.h"
#include "decodethread.h"

QTcpSocket *tcpClient::mySocket = new QTcpSocket;


tcpClient::tcpClient(QObject *parent)
    : QObject{parent}
{

    //计时器处理接收
    connect(timer,&QTimer::timeout,this,[=](){
        QByteArray message = mySocket->readAll();
        readBuffer = readBuffer + message;
        if(readBuffer.length()>=218)
        {
            decodeThread *decode = new decodeThread;
            decode->MutiThreaddecodeMessage(readBuffer.mid(0,218),{1,23});
            connect(decode,&decodeThread::decodeDone,[=](QList<float> temp){
                qDebug()<<temp;//此为处理回的数据
            });
            readBuffer.clear();
        }
    });

    //多线程处理接收
    connect(mySocket,&QTcpSocket::readyRead,this,[=](){
        QByteArray message = mySocket->readAll();
        readBuffer = readBuffer + message;
        if(readBuffer.length()%218==0)
        {
            QThread *tempthread = new QThread;
            decodeThread *decode = new decodeThread;

            decode->moveToThread(tempthread);
            decode->MutiThreaddecodeMessage(readBuffer,{1,23});

            //线程安全退出，要是删除等着电脑卡死
            connect(decode,&decodeThread::finished,tempthread,&QObject::deleteLater);
            connect(tempthread,&QThread::destroyed,tempthread,&QThread::quit);
            tempthread->start();


            connect(decode,&decodeThread::decodeDone,[=](QList<float> temp){
                qDebug()<<temp;//此为处理回的数据
            });

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
        // timer->start(1000/details.sampleRate);//这个是开启接受计时器，由于传感器发送数据过快，为避免拥堵，按照设置采样率去接受处理
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


