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

    static tcpClient *myClient;

    bool isConnected();

    bool connectToControl();
    bool disconnectToControl();

    void openCircleControl(int controlSpeed,int controlChannal);
    void openCircleControl_STOP(int controlChannal);


    void closeCircleControl_Length(lengthControlDetails detail);
    void closeCircleControl_Wave(waveformControlDetails detail);
    void closeCircleControl_Speed();
    void closeCircleControl_STOP(int channal);





    void mode_Stretch();//拉伸运动
    void mode_Compress();//压缩运动
    void mode_Reciprocate();//往复运动


    bool close();
    bool stop();

private:
    controlCommand cmd;
    void delay(int delayTime);
signals:
    void decodeDone(QList<float> decodedData);
};

#endif // CONTROLER_H
