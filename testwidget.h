#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "includeHeader.h"
#include "controler.h"
#include<qsplineseries.h>

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

    static bool freshUiFlag;
    void freshUi();

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

    QSplineSeries *factSeries = new QSplineSeries();
    QSplineSeries *force_time_Series = new QSplineSeries();
    QSplineSeries *length_time_Series = new QSplineSeries();
    QSplineSeries *force_length_Series = new QSplineSeries();
    QSplineSeries *stress_strain_Series = new QSplineSeries();
    QSplineSeries *speed_time_Series = new QSplineSeries();

    QChart *chart = new QChart();

    void drawer();

    float currentForce = 0;//载荷
    QList<float> tempForceList;//载荷

    float currentStress= 0;//应力
    QList<float> tempStressList;//载荷

    float targetLength = 0;//计算位移
    QList<float> temptargetLengthList;//载荷

    float currentLength = 0;//位移传感器
    QList<float> tempLengthList;//载荷

    float currentStrain = 0;//应变
    QList<float> tempStrainList;//载荷

    float currentTime = 0;//时间
    QList<float> tempTimeList;//载荷

    float currentSpeed = 0;//速度
    QList<float> tempSpeedList;//载荷

    float startTime = 0;

    QTimer *autoStopTimer = new QTimer;
    QTimer *uiFreshTimer = new QTimer;
    QTimer *mutiSaveTimer = new QTimer;
    int mutiSaveTime = 500;//强保存时间
    bool tempflag = false;
    int checkWaveId = 1;

    bool smoothFlag = false;

signals:
    void startTest(QString testType);
    void saved();
    void failed();
    void clear();
    void thisShow();
protected:
    void resizeEvent(QResizeEvent *event) override {

        QWidget::resizeEvent(event);

        resize();
        // 在这里执行你自己的处理逻辑
    }
    void resize();


};



#endif // TESTWIDGET_H
