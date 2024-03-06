#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include "includeHeader.h"
#include "decodethread.h"

class tcpClient : public QObject
{
    Q_OBJECT
public:
    explicit tcpClient(QObject *parent = nullptr);

    QStringList getNetWorkIP();

    bool isopen();

    bool tcpConnect();
    bool tcpDisconnect();

    bool sendMessage(QByteArray message);

    TCPFrame messageToTrame(QByteArray message);

    static QTcpSocket *mySocket;

    tcpClient_details details;

    static QByteArray readBuffer;
    static QByteArray mutireadBuffer;
private:

    TCPFrame frame;
    QTimer *timer = new QTimer;
    int kk;
    QMap<QString,decodeThread*>myObj_decodeThread;
    QMap<QString,QThread*>myObj_QThread;

private slots:
    void MutiDecode();

signals:
    void connected();
    void disconnected();
    void decodeDone(QList<float> decodedData);


};

#endif // TCPCLIENT_H
