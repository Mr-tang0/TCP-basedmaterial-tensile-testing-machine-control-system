#ifndef DECODETHREAD_H
#define DECODETHREAD_H

#include <QObject>
#include "includeHeader.h"

class decodeThread : public QObject
{
    Q_OBJECT
public:
    explicit decodeThread(QObject *parent = nullptr);
    void decodeMessage(TCPFrame messageFrame);
    float dataToFloat(QByteArray data);


signals:
};

#endif // DECODETHREAD_H
