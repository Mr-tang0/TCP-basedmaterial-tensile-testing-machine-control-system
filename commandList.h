#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <QString>

struct controlCommand
{
    QString CMD_connent = "W001,1;";//链接
    QString CMD_disconnent = "W001,0;";

    QString CMD_stopOrStart = "W003,%1;";//启动

    QString CMD_openCircleControl = "W03%1,%2;";//开环

    QString CMD_generalControl = "W020,%1;";//波形类别、控制方式

    QString CMD_controlChannal = "W010,%1;";//控制通道

    QString CMD_controlSpeed = "W011,%1;";//控制速度

    QString CMD_targetChannal = "W012,%1;";//目标通道

    QString CMD_targetValue = "W013,%1;";//目标值

    QString CMD_targetAction = "W014,%1;";//动作

    QString CMD_holdTime = "W015,%1;";//持续时间

    QString CMD_outputChannal = "W004,%1;";//输出通道


    QString CMD_amplitudeMaintain = "W%1,%2";//幅度保持开关

    QString CMD_initAngle = "W024,%1;";//初始角度

    QString CMD_frequency = "W021,%1;" ;//波形频率

    QString CMD_amplitude_top = "W022,%1;"; //波形上幅值

    QString CMD_amplitude_bottom = "W023,%1;";//波形下幅值

    QString CMD_waveNumber = "W025,%1;";//波形次数

    QString CMD_initControlSpeed = "W026,%1;";//波形初始速率


    QString CMD_outputPos = "W016,%1;";

    QString CMD_TimeClear = "W160,0;";

};


#endif // COMMANDLIST_H
