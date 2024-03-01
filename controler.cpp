#include "controler.h"

Controler::Controler(QObject *parent)
    : QObject{parent}
{}

bool Controler::isConnected(tcpClient &myTcpClient)
{
    return myTcpClient.isopen();
}

//连接控制器
bool Controler::connectToControl(tcpClient &myTcpClient)
{
    if(!myTcpClient.isopen())
    {
        return false;
    }
    return myTcpClient.sendMessage(cmd.CMD_connent.toUtf8());

}

//断开控制器
bool Controler::disconnectToControl(tcpClient &myTcpClient)
{
    if(!myTcpClient.isopen())
    {
        return false;
    }
    return myTcpClient.sendMessage(cmd.CMD_disconnent.toUtf8());
}


//开环向上运动
void Controler::openCircleControl(tcpClient &myTcpClient,int controlSpeed,int controlChannal)
{
    if(!myTcpClient.isopen())
    {
        return;
    }

    myTcpClient.sendMessage(cmd.CMD_openCircleControl.arg(controlChannal).arg(controlSpeed).toUtf8());

}

//开环停止运动
void Controler::openCircleControl_STOP(tcpClient &myTcpClient,int controlChannal)
{
    if(!myTcpClient.isopen())
    {
        return;
    }

    myTcpClient.sendMessage(cmd.CMD_openCircleControl.arg(controlChannal).arg(0).toUtf8());
}


//常规闭环运动

void Controler::closeCircleControl_Length(tcpClient &myTcpClient,lengthControlDetails detail)
{
    if(!myTcpClient.isopen())
    {
        return;
    }
    //波形0
    myTcpClient.sendMessage(cmd.CMD_generalControl.arg(0).toUtf8());
    //控制通道
    myTcpClient.sendMessage(cmd.CMD_controlChannal.arg(detail.controlChannal).toUtf8());
    //控制速率
    myTcpClient.sendMessage(cmd.CMD_controlSpeed.arg(detail.controlSpeed).toUtf8());
    //目标通道
    myTcpClient.sendMessage(cmd.CMD_targetChannal.arg(detail.targetChannal).toUtf8());
    //目标值
    myTcpClient.sendMessage(cmd.CMD_targetValue.arg(detail.targetValue).toUtf8());
    //到达动作
    myTcpClient.sendMessage(cmd.CMD_targetAction.arg(detail.finishAction).toUtf8());
    //保持时间
    myTcpClient.sendMessage(cmd.CMD_holdTime.arg(detail.holdTime).toUtf8());
    //DA通道
    myTcpClient.sendMessage(cmd.CMD_outputChannal.arg(detail.closeCircleChannal).toUtf8());
    //开始
    myTcpClient.sendMessage(cmd.CMD_stopOrStart.arg(qPow(2,detail.closeCircleChannal)).toUtf8());

}
void Controler::closeCircleControl_Wave(tcpClient &myTcpClient,waveformControlDetails detail)
{
    if(!myTcpClient.isopen())
    {
        return;
    }

    //幅度保持开关
    myTcpClient.sendMessage(cmd.CMD_amplitudeMaintain.arg(484+detail.closeCircleChannal).arg(detail.amplitudeMaintain).toUtf8());

    //波形0
    myTcpClient.sendMessage(cmd.CMD_generalControl.arg(detail.waveType).toUtf8());

    //波形初始角度
    myTcpClient.sendMessage(cmd.CMD_initAngle.arg(detail.initialAngle).toUtf8());

    //波形频率
    myTcpClient.sendMessage(cmd.CMD_frequency.arg(detail.frequency).toUtf8());

    //控制通道
    myTcpClient.sendMessage(cmd.CMD_controlChannal.arg(detail.controlChannal).toUtf8());

    //目标通道
    myTcpClient.sendMessage(cmd.CMD_targetChannal.arg(detail.targetChannal).toUtf8());

    //波形上幅值
    myTcpClient.sendMessage(cmd.CMD_amplitude_top.arg(detail.amplitude_top).toUtf8());

    //波形下幅值
    myTcpClient.sendMessage(cmd.CMD_amplitude_bottom.arg(detail.amplitude_bottom).toUtf8());

    //波形数量
    myTcpClient.sendMessage(cmd.CMD_waveNumber.arg(detail.waveNumber).toUtf8());

    //波形初始速率
    myTcpClient.sendMessage(cmd.CMD_initControlSpeed.arg(detail.controlSpeed).toUtf8());

    //DA通道
    myTcpClient.sendMessage(cmd.CMD_outputChannal.arg(detail.closeCircleChannal).toUtf8());

    //开始
    myTcpClient.sendMessage(cmd.CMD_stopOrStart.arg(512+qPow(2,detail.closeCircleChannal)).toUtf8());
}

void Controler::closeCircleControl_STOP(tcpClient &myTcpClient,int channal)
{
    if(!myTcpClient.isopen())
    {
        return;
    }
    //停止
    myTcpClient.sendMessage(cmd.CMD_stopOrStart.arg(256+qPow(2,channal)).toUtf8());

}


//波形控制运动

void Controler::delay(int delayTime)
{
    QEventLoop loop;
    QTimer::singleShot(delayTime,&loop,SLOT(quit()));
    loop.exec();
}

//运动模式
void Controler::mode_Reciprocate(tcpClient &myTcpClient)
{
    if(!myTcpClient.isopen())
    {
        return;
    }
    myTcpClient.sendMessage(cmd.CMD_generalControl.toUtf8());
    myTcpClient.sendMessage(cmd.CMD_controlChannal.arg("10").toUtf8());
    myTcpClient.sendMessage(cmd.CMD_controlSpeed.arg("10").toUtf8());
    myTcpClient.sendMessage(cmd.CMD_targetChannal.arg("10").toUtf8());
    myTcpClient.sendMessage(cmd.CMD_targetValue.arg("50").toUtf8());

    myTcpClient.sendMessage(cmd.CMD_targetAction.arg("1").toUtf8());
    myTcpClient.sendMessage(cmd.CMD_holdTime.arg("3").toUtf8());

}
