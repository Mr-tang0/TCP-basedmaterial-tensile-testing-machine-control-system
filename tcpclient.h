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
    bool tcpConnect(QString IPAddress, int portNumber);
    bool tcpDisconnect(QString IPAddress, QString portNumber);

    bool sendMessage(QByteArray message);

    static QTcpSocket *mySocket;

private:
    QString netWorkIP;


signals:
    void connected();
    void disconnected();
    void readSomeMessage(QByteArray message);
};

#endif // TCPCLIENT_H
