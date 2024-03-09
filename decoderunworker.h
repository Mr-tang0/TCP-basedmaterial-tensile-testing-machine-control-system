#ifndef DECODERUNWORKER_H
#define DECODERUNWORKER_H

#include <QObject>
#include <QRunnable>
#include <includeHeader.h>


class decodeRunWorker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit decodeRunWorker (QObject *parent = nullptr);


    void MutiThreaddecodeMessage(QByteArray message,QList<int> decodeDataNumber,int id);

    TCPFrame messageToTrame(QByteArray message);
    float dataToFloat(QByteArray data);

signals:

    void finished();
    void decodeDone(QList<float> decodedData);

protected:
    void run() override;

private:
    int iRecvNum;
};

#endif // DECODERUNWORKER_H
