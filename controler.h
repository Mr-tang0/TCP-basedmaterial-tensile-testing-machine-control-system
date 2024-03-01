#ifndef CONTROLER_H
#define CONTROLER_H

#include <QObject>
#include "includeHeader.h"
#include "tcpclient.h"
#include "commandList.h"


class Controler : public QObject
{
    Q_OBJECT
public:
    explicit Controler(QObject *parent = nullptr);


    bool isConnected(tcpClient &myTcpClient);

    bool connectToControl(tcpClient &myTcpClient);
    bool disconnectToControl(tcpClient &myTcpClient);

    void openCircleControl(tcpClient &myTcpClient,int controlSpeed,int controlChannal);
    void openCircleControl_STOP(tcpClient &myTcpClient,int controlChannal);


    void closeCircleControl_Length(tcpClient &myTcpClient,lengthControlDetails detail);
    void closeCircleControl_Wave(tcpClient &myTcpClient,waveformControlDetails detail);
    void closeCircleControl_Speed();
    void closeCircleControl_STOP(tcpClient &myTcpClient,int channal);





    void mode_Stretch(tcpClient &myTcpClient);//拉伸运动
    void mode_Compress(tcpClient &myTcpClient);//压缩运动
    void mode_Reciprocate(tcpClient &myTcpClient);//往复运动


    bool close(tcpClient &myTcpClient);
    bool stop(tcpClient &myTcpClient);

private:
    controlCommand cmd;
    void delay(int delayTime);

signals:
};

#endif // CONTROLER_H
