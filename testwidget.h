#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "includeHeader.h"
#include "controler.h"

namespace Ui {
class testWidget;
}

class testWidget : public QWidget
{
    Q_OBJECT

public:
    explicit testWidget(QWidget *parent = nullptr);
    ~testWidget();
    void saveTest(QString filePath);

public slots:
    void fresh(QList<float> decodeData);

private slots:
    void on_up_clicked();

    void on_stop_clicked();

    void on_down_clicked();

    void on_startTest_clicked();

    void on_setLengthZero_clicked();

    void on_saveTest_clicked();

    void on_stopTest_clicked();

    void on_clearTest_clicked();

    void on_emergency_clicked();

private:
    Ui::testWidget *ui;
    QList<QList<float>> factData;

    QLineSeries *factSeries = new QLineSeries();
    QChart *chart = new QChart();
    void drawer();

    float currentLength = 0;
    float currentTime = 0;
    float startTime = 0;

    int test = 0;
};

#endif // TESTWIDGET_H
