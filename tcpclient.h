#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include "includeHeader.h"


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

private:
    QByteArray readBuffer = "";
    TCPFrame frame;
    QTimer *timer = new QTimer;


signals:
    void connected();
    void disconnected();

};

#endif // TCPCLIENT_H
