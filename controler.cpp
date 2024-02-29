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
void Controler::openCircleControl_UP(tcpClient &myTcpClient,int controlSpeed,int controlChannal)
{
    if(!myTcpClient.isopen())
    {
        return;
    }

    myTcpClient.sendMessage(cmd.CMD_openCircleControl.arg(controlChannal).arg(-controlSpeed).toUtf8());

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

//开环向下运动
void Controler::openCircleControl_DOWN(tcpClient &myTcpClient,int controlSpeed,int controlChannal)
{

    if(!myTcpClient.isopen())
    {
        return;
    }

    myTcpClient.sendMessage(cmd.CMD_openCircleControl.arg(controlChannal).arg(controlSpeed).toUtf8());
}

//闭环定长运动

void Controler::closeCircleControl_length(tcpClient &myTcpClient,int controlSpeed,int controlLength,int controlChannal)
{
    if(!myTcpClient.isopen())
    {
        return;
    }

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
