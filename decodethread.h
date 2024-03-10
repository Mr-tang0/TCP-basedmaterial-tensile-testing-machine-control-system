#ifndef DECODETHREAD_H
#define DECODETHREAD_H

#include <QObject>
#include "includeHeader.h"
#include "decoderunworker.h"

class decodeThread : public QObject
{
    Q_OBJECT

public:
    explicit decodeThread(QObject *parent = nullptr);

    void MutiThreaddecodeMessage(QByteArray message,QList<int> decodeDataNumber);

    TCPFrame messageToTrame(QByteArray message);
    float dataToFloat(QByteArray data);
    void readFile(QString data);

    static bool readFlag;
private:
    // QThreadPool *threadPool = new QThreadPool;
    int threadId = 0;
    QList<decodeRunWorker*> runWorker;
    QList<QThread*> runThread;



signals:
    void finished();
    void decodeDone(QList<float> decodedData);

    void getMessage1(QByteArray message,QList<int> decodeDataNumber,int id);
    void getMessage2(QByteArray message,QList<int> decodeDataNumber,int id);
    void getMessage3(QByteArray message,QList<int> decodeDataNumber,int id);
    void getMessage4(QByteArray message,QList<int> decodeDataNumber,int id);
    void getMessage5(QByteArray message,QList<int> decodeDataNumber,int id);
    void getMessage6(QByteArray message,QList<int> decodeDataNumber,int id);



};

#endif // DECODETHREAD_H
