#include "testwidget.h"
#include "ui_testwidget.h"
#include"mainwindow.h"


bool testWidget::mutiSaveFlag = false;

testWidget::testWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::testWidget)
{
    ui->setupUi(this);
    ui->graphicsView->setChart(chart);

    QLineSeries *temSeries = new QLineSeries;
    chart->addSeries(temSeries);
    *temSeries<<QPointF(0,0);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->removeSeries(temSeries);


    QButtonGroup *myRadioGroup = new QButtonGroup(this);

    myRadioGroup->addButton(ui->radioButton_forceToTime,1);
    myRadioGroup->addButton(ui->radioButton_lengthToTime,2);
    myRadioGroup->addButton(ui->radioButton_forceToLength,3);

    connect(myRadioGroup, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),this,[=](){
        checkWaveId = myRadioGroup->checkedId();
    });
}

testWidget::~testWidget()
{
    delete ui;
}
void testWidget::fresh(QList<float> decodeData)
{
    test++;

    currentForce = decodeData[0];
    ui->load->display(currentForce);

    currentLength = decodeData[1];
    ui->displacement_sensors->display(currentLength-MainWindow::myWorker->details.lengthZero);

    currentTime = decodeData[2];
    ui->Duration->display(currentTime-startTime);

    *force_time_Series<<QPointF(currentTime,currentForce);

    *length_time_Series<<QPointF(currentTime,currentLength);

    *force_length_Series<<QPointF(currentLength-MainWindow::myWorker->details.lengthZero,currentForce);

    float tempLenth = currentLength-MainWindow::myWorker->details.lengthZero;
    float tempTime = currentTime - startTime;
    float tempForce = currentForce;

    QList<float> temp = {tempTime,tempForce,tempLenth};
    factData.append(temp);



    switch (checkWaveId) {
    case 1:
        if(!chart->series().isEmpty())
        {
            chart->removeSeries(force_time_Series);
            chart->removeSeries(length_time_Series);
            chart->removeSeries(force_length_Series);
        }
        chart->addSeries(force_time_Series);
        break;
    case 2:
        if(!chart->series().isEmpty())
        {
            chart->removeSeries(force_time_Series);
            chart->removeSeries(length_time_Series);
            chart->removeSeries(force_length_Series);
        }
        chart->addSeries(length_time_Series);
        break;
    case 3:
        if(!chart->series().isEmpty())
        {
            chart->removeSeries(force_time_Series);
            chart->removeSeries(length_time_Series);
            chart->removeSeries(force_length_Series);
        }
        chart->addSeries(force_length_Series);
        break;
        break;
    default:
        break;
    }

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
    MainWindow::myControler->disconnectToControl();
}


void testWidget::on_down_clicked()
{
    MainWindow::myControler->openCircleControl(ui->matul->value(),3);
}


void testWidget::on_startTest_clicked()
{
    startTime = currentTime;
    force_time_Series->clear();
    length_time_Series->clear();
    force_length_Series->clear();
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
        detail.frequency = MainWindow::myWorker->details.frequency;
        detail.controlSpeed = MainWindow::myWorker->details.cycleSpeed;
        detail.amplitude_top = MainWindow::myWorker->details.lengthZero-MainWindow::myWorker->details.cycleLength;
        detail.amplitude_bottom = MainWindow::myWorker->details.lengthZero+MainWindow::myWorker->details.cycleLength;
        detail.waveNumber = MainWindow::myWorker->details.cycleNumber;
        MainWindow::myControler->closeCircleControl_Wave(detail);

    }
    if(mutiSaveFlag)
    {
        tcpClient::mutireadBuffer.clear();
        connect(mutiSaveTimer,&QTimer::timeout,this,[=](){
            if(tempflag)
            {
                MainWindow::myControler->disconnectToControl();

                StrongSaveTest("D:\\appfile\\tempdata.csv");
                qDebug()<<"STOP!";
                mutiSaveTimer->stop();
            }
            tempflag = !tempflag;
            qDebug()<<tempflag;
        });
        mutiSaveTimer->start(600);
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
        out<<"time";
        out<<",";
        out<<"force";
        out<<",";
        out<<"length";
        out<<"\n";

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
void testWidget::StrongSaveTest(QString filePath)
{
    QFile labelFile(filePath);
    if(!labelFile.open(QIODevice::Append|QIODevice::Text))
    {
        qDebug()<<"指定位置不存在!";
    }
    else {
        QTextStream out(&labelFile);
        int strLength = tcpClient::mutireadBuffer.length()/218;
        for(int i = 0;i<strLength;i++)
        {
            out<<tcpClient::mutireadBuffer.mid(i*218,218).toHex().toStdString().c_str();

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
    saveTest(MainWindow::myWorker->details.filePath+"\\testdata.csv");
}


void testWidget::on_stopTest_clicked()
{
    MainWindow::myControler->openCircleControl_STOP(3);
    MainWindow::myControler->disconnectToControl();
    factSeries->clear();
}


void testWidget::on_clearTest_clicked()
{
    force_time_Series->clear();
    length_time_Series->clear();
    force_length_Series->clear();
}


void testWidget::on_emergency_clicked()
{
    MainWindow::myControler->openCircleControl_STOP(3);
}


void testWidget::on_mutiSave_clicked()
{
    StrongSaveTest(MainWindow::myWorker->details.filePath+"\\tempdata.csv");
}


void testWidget::on_mutiSaveOpen_toggled(bool checked)
{
    mutiSaveFlag = checked;

    if(mutiSaveFlag)
    {
        qDebug()<<"checked";

        QMessageBox msgBox;
        msgBox.setText("警告：非必要不要用，严格按照说明执行本开关程序，否则可能会损坏机器！");
        msgBox.exec();
    }
    else
    {
        qDebug()<<"released";
    }

}

