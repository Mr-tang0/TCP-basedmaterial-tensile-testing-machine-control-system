#include "decodethread.h"

decodeThread::decodeThread(QObject *parent)
    : QObject{parent}
{

    for (int i = 0; i < 7; ++i) {
        runWorker.append(new decodeRunWorker);
        runThread.append(new QThread);
        runWorker[i]->moveToThread(runThread[i]);
        runThread[i]->start();
    }

    connect(this,&decodeThread::getMessage1,[=](QByteArray message,QList<int> decodeDataNumber,int id){
        runWorker[0]->MutiThreaddecodeMessage(message,decodeDataNumber,id);
    });
    connect(this,&decodeThread::getMessage2,[=](QByteArray message,QList<int> decodeDataNumber,int id){
        runWorker[1]->MutiThreaddecodeMessage(message,decodeDataNumber,id);
    });
    connect(this,&decodeThread::getMessage3,[=](QByteArray message,QList<int> decodeDataNumber,int id){
        runWorker[2]->MutiThreaddecodeMessage(message,decodeDataNumber,id);
    });
    connect(this,&decodeThread::getMessage4,[=](QByteArray message,QList<int> decodeDataNumber,int id){
        runWorker[3]->MutiThreaddecodeMessage(message,decodeDataNumber,id);
    });
    connect(this,&decodeThread::getMessage5,[=](QByteArray message,QList<int> decodeDataNumber,int id){
        runWorker[4]->MutiThreaddecodeMessage(message,decodeDataNumber,id);
    });
    connect(this,&decodeThread::getMessage6,[=](QByteArray message,QList<int> decodeDataNumber,int id){
        runWorker[6]->MutiThreaddecodeMessage(message,decodeDataNumber,id);
    });


}

void decodeThread::MutiThreaddecodeMessage(QByteArray message,QList<int> decodeDataNumber)
{
    // switch (threadId) {
    // case 0:
    //     emit getMessage1(message,decodeDataNumber,threadId);
    //     break;
    // case 1:
    //     emit getMessage2(message,decodeDataNumber,threadId);
    //     break;
    // case 2:
    //     emit getMessage3(message,decodeDataNumber,threadId);
    //     break;
    // case 3:
    //     emit getMessage4(message,decodeDataNumber,threadId);
    //     break;
    // case 4:
    //     emit getMessage5(message,decodeDataNumber,threadId);
    //     break;
    // case 5:
    //     emit getMessage6(message,decodeDataNumber,threadId);
    //     break;
    // default:
    //     break;
    // }

    // threadId++;
    // if(threadId>6)threadId=0;
    // 0:S0力，10：S10计算位移,13：S13位移传感,29：时间

    for (int i = 0; i < message.length()/218; i++)
    {

        TCPFrame frame = messageToTrame(message.left(218));
        message.remove(0,218);
        QList<float> decodeData;
        foreach (int item, decodeDataNumber) {
            float decode = dataToFloat(frame.data[item]);
            decodeData.append(decode);
        }
        emit decodeDone(decodeData);
    }

    emit finished();
}

TCPFrame decodeThread::messageToTrame(QByteArray message)
{
    TCPFrame tempFrame;
    tempFrame.header = message.mid(0,10);
    tempFrame.tail = message.right(4);

    for(int i = 0;i<51;i++)
    {
        tempFrame.data.append(message.mid(10+4*i,4));
    }

    return tempFrame;
}

float decodeThread::dataToFloat(QByteArray data)//小端数据
{
    //转大端
    QByteArray bigEndian;
    for (int i = 0; i<4;i++)
    {
        bigEndian =  data.mid(i,1) + bigEndian;
    }

    float result = 0;
    int size = bigEndian.size();
    char* data_char = bigEndian.data();
    char* p = (char*)&result;
    for(int index = 0; index < size; index++)
    {
        *(p + index) = *(data_char + size - 1 - index);
    }

    return result;

}
void decodeThread::readFile(QString data)
{
    int i = 0;

    bool ok;

    for (const QString &chunk : data.split("\n"))
    {
        if(i!=0)//去表头
        {
            QList<float> tempDecodeData;

            for (const QString &temp : chunk.split(","))
            {
                float value= temp.toFloat(&ok);
                if(ok)tempDecodeData.append(value);
            }
            emit decodeDone(tempDecodeData);

            QEventLoop loop;
            QTimer::singleShot(100,&loop,SLOT(quit()));
            loop.exec();
        }
        i++;
    }


}

