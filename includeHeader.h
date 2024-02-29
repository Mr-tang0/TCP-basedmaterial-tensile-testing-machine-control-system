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

#endif // INCLUDEHEADER_H
