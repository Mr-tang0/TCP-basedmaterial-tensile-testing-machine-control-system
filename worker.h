#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "includeHeader.h"


class worker : public QObject
{
    Q_OBJECT
public:
    explicit worker(QObject *parent = nullptr);

    static workerDetails details;//测试信息

    void getSystemSet();//系统设置
    void getTestDetails();//测试设置

private:

signals:
};

#endif // WORKER_H
