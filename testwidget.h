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

    void initThis();
    // RangeSlider* rangeSliderThre = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
    void resizeChart(int low,int high);

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


    // void on_OK_clicked();

    void on_checkBox_forceToTime_toggled(bool checked);

    void on_checkBox_lengthToTime_toggled(bool checked);

    void on_checkBox_speedTotime_toggled(bool checked);

    void on_checkBox_forceToLength_toggled(bool checked);

    void on_checkBox_stresToStrain_toggled(bool checked);

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
    QSplineSeries *speed_time_Series = new QSplineSeries();

    QChart *chart = new QChart();

    float currentForce = 0;//载荷
    QList<float> tempForceList;//载荷
    QList<float> ForceList;//载荷


    float currentStress= 0;//应力
    QList<float> StressList;


    float targetLength = 0;//计算位移
    QList<float> temptargetLengthList;//载荷
    QList<float> targetLengthList;//载荷



    float currentLength = 0;//位移传感器
    QList<float> LengthList;//载荷


    float currentStrain = 0;//应变
    QList<float> StrainList;//载荷


    float currentTime = 0;//时间
    QList<float> tempTimeList;//载荷
    QList<float> TimeList;//载荷


    float currentSpeed = 0;//速度
    QList<float> SpeedList;//载荷


    float startTime = 0;

    QTimer *autoStopTimer = new QTimer;
    QTimer *uiFreshTimer = new QTimer;
    QTimer *mutiSaveTimer = new QTimer;
    int mutiSaveTime = 1500;//强保存时间
    bool tempflag = false;
    int checkWaveId = 1;
    QList<int> WaveId = {1};

    bool smoothFlag = false;

    bool leftButtonPressedFlag;
    QPoint m_oPrePos;

    QValueAxis *timeAxis = new QValueAxis;
    QValueAxis *forceAxis = new QValueAxis;
    QValueAxis *TargetAxis = new QValueAxis;
    QValueAxis *lengthAxis = new QValueAxis;
    QValueAxis *stressAxis = new QValueAxis;
    QValueAxis *strainAxis = new QValueAxis;
    QValueAxis *speedAxis = new QValueAxis;

    int listLow = 0;
    int listHigh = 9999999;
    float max(QList<float> t,int low,int high)
    {
        if(t.length()<high)high = t.length();
        QList<float> temp = t.mid(low,high);

        float m = temp.first();
        if(!temp.isEmpty())
        {
            foreach (float item, temp) {
                if(item>m)m= item;
            }
        }
        // m = QString::number(m, 'f', 2).toDouble();
        return m;
    }

    float min(QList<float> t,int low,int high){
        if(t.length()<high)high = t.length();
        QList<float> temp = t.mid(low,high);

        float m = temp.first();
        if(!temp.isEmpty())
        {
            foreach (float item, temp) {
                if(item<m)m= item;
            }
        }
        // m = QString::number(m, 'f', 2).toDouble();
        return m;
    }


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

    }
    void resize();

    // virtual void mousePressEvent(QMouseEvent *event) override;
    // virtual void mouseReleaseEvent(QMouseEvent *event)override;
    // // virtual void mouseDoubleClickEvent(QMouseEvent *event)override;
    // virtual void mouseMoveEvent(QMouseEvent *event)override;
    // virtual void wheelEvent(QWheelEvent *event)override;


    float wheelSize = 1;


};



#endif // TESTWIDGET_H
