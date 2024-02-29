#include "controler.h"

Controler::Controler(QObject *parent)
    : QObject{parent}
{}

bool Controler::open(tcpClient &myTcpClient)
{
    if(myTcpClient.isopen())
    {
        myTcpClient.sendMessage("I'm in Controler Already!");
    }
    return false;
}

bool Controler::connectToControl(tcpClient &myTcpClient)
{
    if(!myTcpClient.isopen())
    {
        return false;
    }
    myTcpClient.sendMessage(cmd.CMD_connent.toUtf8());

    return false;
}

void Controler::openCircleControl_UP(tcpClient &myTcpClient,int controlSpeed,int controlChannal)
{
    if(!myTcpClient.isopen())
    {
        return;
    }

    myTcpClient.sendMessage(cmd.CMD_openCircleControl.arg(controlChannal).arg(-controlSpeed).toUtf8());

}
void Controler::openCircleControl_DOWN(tcpClient &myTcpClient,int controlSpeed,int controlChannal)
{
    if(!myTcpClient.isopen())
    {
        return;
    }
    if(!myTcpClient.isopen())
    {
        return;
    }

    myTcpClient.sendMessage(cmd.CMD_openCircleControl.arg(controlChannal).arg(controlSpeed).toUtf8());
}

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
