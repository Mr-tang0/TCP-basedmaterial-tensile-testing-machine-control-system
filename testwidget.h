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
    void StrongSaveTest(QString filePath);

    static bool mutiSaveFlag;

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

    void on_mutiSave_clicked();

    void on_mutiSaveOpen_toggled(bool checked);

    void on_autoMove_toggled(bool checked);

private:
    Ui::testWidget *ui;
    QList<QList<float>> factData;
    bool autoFlag = false;
    void autoToZreoForce(int targetForce);
    QTimer *autoTimer = new QTimer;

    QLineSeries *factSeries = new QLineSeries();
    QLineSeries *force_time_Series = new QLineSeries();
    QLineSeries *length_time_Series = new QLineSeries();
    QLineSeries *force_length_Series = new QLineSeries();
    QLineSeries *stress_strain_Series = new QLineSeries();
    QChart *chart = new QChart();
    void drawer();

    float currentForce = 0;//载荷
    float currentStress= 0;//应力
    float targetLength = 0;//计算位移
    float currentLength = 0;//位移传感器
    float currentStrain = 0;//应变
    float currentTime = 0;//时间
    float startTime = 0;

    QTimer *mutiSaveTimer = new QTimer;
    int mutiSaveTime = 500;//强保存时间
    bool tempflag = false;
    int checkWaveId = 1;
signals:
    void startTest(QString testType);
    void saved();
    void failed();
    void clear();
};

#endif // TESTWIDGET_H
