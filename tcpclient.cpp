#include "tcpclient.h"
#include "testwidget.h"

QTcpSocket *tcpClient::mySocket = new QTcpSocket;
QByteArray tcpClient::readBuffer = "";
QByteArray tcpClient::mutireadBuffer = "";

tcpClient::tcpClient(QObject *parent)
    : QObject{parent}
{

    //计时器处理接收
    decodeThread *decode = new decodeThread;
    QThread *myThread = new QThread;
    decode->moveToThread(myThread);
    myThread->start();

    connect(timer,&QTimer::timeout,this,[=](){
        QByteArray message = mySocket->readAll();

        readBuffer = readBuffer + message;

        if(readBuffer.length()>=218)
        {
            decode->MutiThreaddecodeMessage(readBuffer.mid(0,218),{0,10,13,29});
            readBuffer.clear();
        }
    });

    connect(decode,&decodeThread::decodeDone,[=](QList<float> decodeData){
        emit decodeDone(decodeData);
    });

    // 多线程处理接收
    kk=0;
    connect(mySocket,&QTcpSocket::readyRead,this,[=](){
        if(testWidget::mutiSaveFlag)
        {
            timer->stop();
            QByteArray message = mySocket->readAll();
            mutireadBuffer = mutireadBuffer + message;
        }
        else
        {
            // timer->start(10);
            timer->start(1000/details.sampleRate);//这个是开启接受计时器，由于传感器发送数据过快，为避免拥堵，按照设置采样率去接受处理
        }
    });

    connect(mySocket,&QTcpSocket::connected,this, [=](){
        // timer->start(10);
        timer->start(1000/details.sampleRate);//这个是开启接受计时器，由于传感器发送数据过快，为避免拥堵，按照设置采样率去接受处理
        emit connected();
    });

    connect(mySocket,&QTcpSocket::disconnected,this,[=](){
        qDebug()<<"disconnected!";
        timer->stop();
        emit disconnected();
    });

}
void tcpClient::MutiDecode()
{


    QString randomDecodeName = "decode"+QString::number(QRandomGenerator::global()->generate());
    QString randomthreadName = "thread"+QString::number(QRandomGenerator::global()->generate());

    qDebug()<<kk<<randomDecodeName<<randomthreadName;

    decodeThread *decode = new decodeThread();
    myObj_decodeThread.insert(randomDecodeName,decode);
    QThread *tempthread = new QThread;
    myObj_QThread.insert(randomthreadName,tempthread);

    myObj_decodeThread[randomDecodeName]->moveToThread(myObj_QThread[randomthreadName]);
    myObj_decodeThread[randomDecodeName]->MutiThreaddecodeMessage(readBuffer,{0,10,13,29});

    myObj_QThread[randomthreadName]->start();

    connect(myObj_decodeThread[randomDecodeName],&decodeThread::finished,[=](){
        myObj_QThread[randomthreadName]->deleteLater();
        myObj_decodeThread[randomDecodeName]->deleteLater();
        kk = kk-1;
        qDebug()<<"delete";
    });
    connect(myObj_QThread[randomthreadName],&QThread::destroyed,myObj_QThread[randomthreadName],&QThread::quit);

    connect(myObj_decodeThread[randomDecodeName],&decodeThread::decodeDone,[=](QList<float> temp){
        qDebug()<<temp;//此为处理回的数据
    });

    readBuffer.clear();
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

    return mySocket->isOpen();
}

bool tcpClient::tcpDisconnect()
{
    return mySocket->disconnect();
}

bool tcpClient::sendMessage(QByteArray message)
{
    qDebug()<<"message"<<message;
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


