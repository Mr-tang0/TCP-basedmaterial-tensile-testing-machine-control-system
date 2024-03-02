#include "testwidget.h"
#include "ui_testwidget.h"
#include"mainwindow.h"

testWidget::testWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::testWidget)
{
    ui->setupUi(this);
    ui->graphicsView->setChart(chart);
    chart->addSeries(factSeries);
    chart->legend()->hide();
    chart->createDefaultAxes();


}

testWidget::~testWidget()
{
    delete ui;
}
void testWidget::fresh(QList<float> decodeData)
{
    ui->load->display(decodeData[0]);
    ui->displacement_sensors->display(decodeData[1]-MainWindow::myWorker->details.lengthZero);
    currentLength = decodeData[1];
    ui->Duration->display(decodeData[2]-startTime);
    currentTime = decodeData[2];

    test++;
    *factSeries<<QPointF(decodeData[2],decodeData[0]);

    float tempLenth = decodeData[1]-MainWindow::myWorker->details.lengthZero;
    float tempTime = decodeData[2] - startTime;

    QList<float> temp = {tempTime,decodeData[0],tempLenth};
    factData.append(temp);

    if(!chart->series().isEmpty())chart->removeSeries(factSeries);
    chart->addSeries(factSeries);
    chart->legend()->hide();
    chart->createDefaultAxes();

}

void testWidget::drawer()
{
    if(!chart->series().isEmpty())chart->removeSeries(factSeries);
    chart->addSeries(factSeries);
    chart->legend()->hide();
    chart->createDefaultAxes();
}




void testWidget::on_up_clicked()
{

    MainWindow::myControler->openCircleControl(-ui->matul->value(),3);
}


void testWidget::on_stop_clicked()
{
    MainWindow::myControler->openCircleControl_STOP(3);
}


void testWidget::on_down_clicked()
{
    MainWindow::myControler->openCircleControl(ui->matul->value(),3);
}


void testWidget::on_startTest_clicked()
{
    startTime = currentTime;
    factSeries->clear();
    factData.clear();

    qDebug()<<startTime;
    if(MainWindow::myWorker->details.testType=="拉伸")
    {
        lengthControlDetails detail;

        detail.controlSpeed = MainWindow::myWorker->details.speed;
        detail.targetValue = MainWindow::myWorker->details.lengthZero+MainWindow::myWorker->details.length;
        MainWindow::myControler->closeCircleControl_Length(detail);
    }
    else if(MainWindow::myWorker->details.testType=="压缩")
    {
        lengthControlDetails detail;

        detail.controlSpeed = MainWindow::myWorker->details.speed;
        detail.targetValue = MainWindow::myWorker->details.lengthZero-MainWindow::myWorker->details.length;
        MainWindow::myControler->closeCircleControl_Length(detail);
    }
    else
    {
        waveformControlDetails detail;

        detail.waveType = MainWindow::myWorker->details.WaveTypeNumber;
        detail.frequency = MainWindow::myWorker->details.cycleTime;
        detail.controlSpeed = MainWindow::myWorker->details.cycleSpeed;
        detail.amplitude_top = MainWindow::myWorker->details.lengthZero-MainWindow::myWorker->details.cycleLength;
        detail.amplitude_bottom = MainWindow::myWorker->details.lengthZero+MainWindow::myWorker->details.cycleLength;

    }

}
void testWidget::saveTest(QString filePath)
{
    QFile labelFile(filePath);
    if(!labelFile.open(QIODevice::Append|QIODevice::Text))
    {
        qDebug()<<"指定位置不存在!";
    }
    else {
        QTextStream out(&labelFile);

        for (int i = 0;i<factData.length();i++)
        {
            for (int j = 0;j<factData[i].length();j++)
            {
                out<<QString::number(factData[i][j]).toUtf8().toStdString().c_str();
                out<<",";
            }
            out<<"\n";
        }
        labelFile.close();
    }

    qDebug()<<"保存成功！";
}


void testWidget::on_setLengthZero_clicked()
{
    MainWindow::myWorker->details.lengthZero = currentLength;
    qDebug()<<"zero:"<<currentLength;
}


void testWidget::on_saveTest_clicked()
{
    saveTest("D:\\appfile\\Testdata.csv");
}


void testWidget::on_stopTest_clicked()
{
    MainWindow::myControler->openCircleControl_STOP(3);
    factSeries->clear();
}


void testWidget::on_clearTest_clicked()
{
    factSeries->clear();
    lengthControlDetails detail;

    detail.controlSpeed = MainWindow::myWorker->details.speed;
    detail.targetValue = MainWindow::myWorker->details.lengthZero+MainWindow::myWorker->details.length;
    MainWindow::myControler->closeCircleControl_Length(detail);
}


void testWidget::on_emergency_clicked()
{
    MainWindow::myControler->openCircleControl_STOP(3);
}

