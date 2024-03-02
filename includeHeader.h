#ifndef INCLUDEHEADER_H
#define INCLUDEHEADER_H


#include "qtmaterialsnackbar.h"
#include "qtmaterialflatbutton.h"

#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QButtonGroup>
#include <QRadioButton>
#include <QAbstractButton>
#include <QVBoxLayout>
#include <QDataStream>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QThread>
#include <QEventLoop>
#include <QFileDialog>
#include <QtCore/qmath.h>
#include <QMessageBox>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
//charts宏
QT_CHARTS_USE_NAMESPACE


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

struct workerDetails
{
    QString UseName = "admin";
    QString Number = "000000";
    QString testTime = "2099-01-01-00:00:00";
    QString testType = "la";
    QString filePath = "C:/";

    //拉伸或压缩
    double speed = 1;//速度mm/s
    double length = 1;//运动距离mm
    double maxSpeed = 99;//最大速度设置
    double maxLength = 99;//最大运动距离
    double maxTime = 99;//最大运动时间

    //往返
    int WaveTypeNumber = 1;//1 正弦波输出 2 三角波输出 3 方波输出 4 其他波形
    double cycleSpeed = 1;//速度mm/s
    double cycleLength = 1;//运动距离mm
    double cycleTime = 1;//往返运动周期s
    double cycleNumber = 100;
    double cycleMaxTime;//最大运动时间

    double lengthZero = 10;//约定距离0点
    double forceZero = 10;//约定力0点
    double Backlash = 0;//背隙补偿值
    int stopAction = 0;//停止条件
    double stopActionValue = 10;//停止条件值
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

    float holdTime = 0;//持续时间

    int closeCircleChannal = 3;//输出通道

};

#endif // INCLUDEHEADER_H
