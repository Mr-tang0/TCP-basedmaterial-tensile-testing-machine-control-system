#ifndef INCLUDEHEADER_H
#define INCLUDEHEADER_H


#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>

#include <QVBoxLayout>
#include <QDataStream>
#include <QTimer>

#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include<QThread>
#include <QEventLoop>

#include <QtCore/qmath.h>

struct tcpClient_details
{
    QString netWorkIP;
    int portNumber;

    int sampleRate;
};

struct TCPFrame//218
{
    QByteArray header;//10

    QByteArrayList data;//204

    QByteArray tail;//4
};

struct motorDetails
{
    int motorID;//地址

    double speed;//速度
    double maxSpeed;//最大速度设置
    double length;//运动距离
    double maxLength;//最大运动距离

    double cycle;//往返运动周期

    double pitch;//螺距
    double currentAngle;//当前运动距离

    double zero;//约定0点
    double Backlash;//背隙补偿值
};

struct waveformControlDetails
{
    int amplitudeMaintain = 0;//幅度保持

    int waveType = 1;//波形

    float initialAngle = 0;//波形初始角度

    float frequency = 1;//波形频率

    int controlChannal = 10;//控制通道

    int targetChannal = 10;//目标通道

    float amplitude_top = 40;//上下幅值
    float amplitude_bottom = 30;//上下幅值

    int waveNumber = 100;//波形次数

    float controlSpeed = 1;//波形初始速率

    int closeCircleChannal = 3;//输出通道

};

struct lengthControlDetails
{
    int controlChannal = 10;//控制通道

    float controlSpeed = 1;//控制速度

    int targetChannal =10;//目标通道

    float targetValue =35;//目标值

    int finishAction = 1;//动作

    float holdTime = 10;//持续时间

    int closeCircleChannal = 3;//输出通道

};

#endif // INCLUDEHEADER_H
