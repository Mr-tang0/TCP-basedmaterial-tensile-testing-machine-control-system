#ifndef DECODETHREAD_H
#define DECODETHREAD_H

#include <QObject>
#include "includeHeader.h"

class decodeThread : public QObject
{
    Q_OBJECT
public:
    explicit decodeThread(QObject *parent = nullptr);

    void MutiThreaddecodeMessage(QByteArray message,QList<int> decodeDataNumber);

    TCPFrame messageToTrame(QByteArray message);
    float dataToFloat(QByteArray data);


signals:
    void finished();
    void decodeDone(QList<float> decodedData);
};

#endif // DECODETHREAD_H
