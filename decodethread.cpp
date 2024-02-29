#include "decodethread.h"

decodeThread::decodeThread(QObject *parent)
    : QObject{parent}
{

}

void decodeThread::decodeMessage(TCPFrame messageFrame)
{


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

