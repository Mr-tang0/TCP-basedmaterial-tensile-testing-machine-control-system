#include "decoderunworker.h"

decodeRunWorker::decodeRunWorker(QObject *parent) : QObject(parent), QRunnable()
{
    //设置自动析构
    setAutoDelete(false);

}


void decodeRunWorker::run(){
    qDebug() <<" 线程："<< iRecvNum<<" || "<<QThread::currentThread();
}

void decodeRunWorker::MutiThreaddecodeMessage(QByteArray message,QList<int> decodeDataNumber,int id)
{
    iRecvNum = id;

    qDebug() <<" 线程："<< iRecvNum<<" || "<<QThread::currentThread();
    //0:S0力，10：S10计算位移,13：S13位移传感,29：时间

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

TCPFrame decodeRunWorker::messageToTrame(QByteArray message)
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

float decodeRunWorker::dataToFloat(QByteArray data)//小端数据
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
