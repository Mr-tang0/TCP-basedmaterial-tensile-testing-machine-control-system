#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include "includeHeader.h"

class motor : public QObject
{
    Q_OBJECT
public:
    explicit motor(QObject *parent = nullptr);



    bool open(QTcpSocket &mySocket);

    bool close(QTcpSocket &mySocket);
    bool stop(QTcpSocket &mySocket);

    struct details
    {
        QString port = "";//端口

    };
signals:
};

#endif // MOTOR_H
