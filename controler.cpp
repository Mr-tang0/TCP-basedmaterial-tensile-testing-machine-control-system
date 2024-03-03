#include "controler.h"

tcpClient *Controler::myClient = new tcpClient;

Controler::Controler(QObject *parent)
    : QObject{parent}
{


}

bool Controler::isConnected()
{
    return myClient->isopen();
}

//连接控制器
bool Controler::connectToControl(QString IP,int port,int samplerate)
{
    myClient->details.netWorkIP = IP;
    myClient->details.portNumber = port;
    myClient->details.sampleRate = samplerate;

    myClient->tcpConnect();

    if(!myClient->isopen())
    {
        return false;
    }

    connect(myClient,&tcpClient::decodeDone,this,[=](QList<float> decodedData){
        emit decodeDone(decodedData);
    });
    bool flag = myClient->sendMessage(cmd.CMD_connent.toUtf8());

    return flag;

}

//断开控制器
bool Controler::disconnectToControl()
{
    if(!myClient->isopen())
    {
        return false;
    }
    return myClient->sendMessage(cmd.CMD_disconnent.toUtf8());
}


//开环向上运动
void Controler::openCircleControl(int controlSpeed,int controlChannal)
{
    if(!myClient->isopen())
    {
        return;
    }

    myClient->sendMessage(cmd.CMD_openCircleControl.arg(controlChannal).arg(controlSpeed).toUtf8());

}

//开环停止运动
void Controler::openCircleControl_STOP(int controlChannal)
{
    if(!myClient->isopen())
    {
        return;
    }

    myClient->sendMessage(cmd.CMD_openCircleControl.arg(controlChannal).arg(0).toUtf8());
}


//常规闭环运动

void Controler::closeCircleControl_Length(lengthControlDetails detail)
{
    if(!myClient->isopen())
    {
        return;
    }
    //波形0
    myClient->sendMessage(cmd.CMD_generalControl.arg(0).toUtf8());
    //控制通道
    myClient->sendMessage(cmd.CMD_controlChannal.arg(detail.controlChannal).toUtf8());
    //控制速率
    myClient->sendMessage(cmd.CMD_controlSpeed.arg(detail.controlSpeed).toUtf8());
    //目标通道
    myClient->sendMessage(cmd.CMD_targetChannal.arg(detail.targetChannal).toUtf8());
    //目标值
    myClient->sendMessage(cmd.CMD_targetValue.arg(detail.targetValue).toUtf8());
    //到达动作
    myClient->sendMessage(cmd.CMD_targetAction.arg(detail.finishAction).toUtf8());
    //保持时间
    myClient->sendMessage(cmd.CMD_holdTime.arg(detail.holdTime).toUtf8());
    //DA通道
    myClient->sendMessage(cmd.CMD_outputChannal.arg(detail.closeCircleChannal).toUtf8());
    //开始
    myClient->sendMessage(cmd.CMD_stopOrStart.arg(qPow(2,detail.closeCircleChannal)).toUtf8());

}
void Controler::closeCircleControl_Wave(waveformControlDetails detail)
{
    if(!myClient->isopen())
    {
        return;
    }

    //幅度保持开关
    myClient->sendMessage(cmd.CMD_amplitudeMaintain.arg(484+detail.closeCircleChannal).arg(detail.amplitudeMaintain).toUtf8());

    //波形0
    myClient->sendMessage(cmd.CMD_generalControl.arg(detail.waveType).toUtf8());

    //波形初始角度
    myClient->sendMessage(cmd.CMD_initAngle.arg(detail.initialAngle).toUtf8());

    //波形频率
    myClient->sendMessage(cmd.CMD_frequency.arg(detail.frequency).toUtf8());

    //控制通道
    myClient->sendMessage(cmd.CMD_controlChannal.arg(detail.controlChannal).toUtf8());

    //目标通道
    myClient->sendMessage(cmd.CMD_targetChannal.arg(detail.targetChannal).toUtf8());

    //波形上幅值
    myClient->sendMessage(cmd.CMD_amplitude_top.arg(detail.amplitude_top).toUtf8());

    //波形下幅值
    myClient->sendMessage(cmd.CMD_amplitude_bottom.arg(detail.amplitude_bottom).toUtf8());

    //波形数量
    myClient->sendMessage(cmd.CMD_waveNumber.arg(detail.waveNumber).toUtf8());

    //波形初始速率
    myClient->sendMessage(cmd.CMD_initControlSpeed.arg(detail.controlSpeed).toUtf8());

    //DA通道
    myClient->sendMessage(cmd.CMD_outputChannal.arg(detail.closeCircleChannal).toUtf8());

    //开始
    myClient->sendMessage(cmd.CMD_stopOrStart.arg(512+qPow(2,detail.closeCircleChannal)).toUtf8());
}

void Controler::closeCircleControl_STOP(int channal)
{
    if(!myClient->isopen())
    {
        return;
    }
    //停止
    myClient->sendMessage(cmd.CMD_stopOrStart.arg(256+qPow(2,channal)).toUtf8());

}


//波形控制运动

void Controler::delay(int delayTime)
{
    QEventLoop loop;
    QTimer::singleShot(delayTime,&loop,SLOT(quit()));
    loop.exec();
}

//运动模式
void Controler::mode_Reciprocate()
{
    if(!myClient->isopen())
    {
        return;
    }
    myClient->sendMessage(cmd.CMD_generalControl.toUtf8());
    myClient->sendMessage(cmd.CMD_controlChannal.arg("10").toUtf8());
    myClient->sendMessage(cmd.CMD_controlSpeed.arg("10").toUtf8());
    myClient->sendMessage(cmd.CMD_targetChannal.arg("10").toUtf8());
    myClient->sendMessage(cmd.CMD_targetValue.arg("50").toUtf8());

    myClient->sendMessage(cmd.CMD_targetAction.arg("1").toUtf8());
    myClient->sendMessage(cmd.CMD_holdTime.arg("3").toUtf8());

}
