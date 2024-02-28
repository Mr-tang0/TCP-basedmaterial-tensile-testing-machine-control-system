#ifndef DECODETHREAD_H
#define DECODETHREAD_H

#include <QObject>

class decodeThread : public QObject
{
    Q_OBJECT
public:
    explicit decodeThread(QObject *parent = nullptr);

signals:
};

#endif // DECODETHREAD_H
