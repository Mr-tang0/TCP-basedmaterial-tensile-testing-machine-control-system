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
    myRadioGroup->addButton(ui->radioButton_stresToStrain,4);

    connect(myRadioGroup, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),this,[=](){
        checkWaveId = myRadioGroup->checkedId();
        fresh({currentForce,targetLength,currentLength,currentTime});
    });

    connect(ui->load,&myLcdNumber::doubleClicked,this,[=](){
        MainWindow::myControler->channalClear(0);
    });
    connect(ui->displacement,&myLcdNumber::doubleClicked,this,[=](){
        MainWindow::myControler->channalClear(10);
    });
    connect(ui->displacement_sensors,&myLcdNumber::doubleClicked,this,[=](){
        MainWindow::myControler->channalClear(13);
    });
    connect(ui->Duration,&myLcdNumber::doubleClicked,this,[=](){
        MainWindow::myControler->channalClear(20);
    });

    connect(ui->smoothCurve,&QCheckBox::toggled,[=](bool choose){
        if(choose)
        {
            qDebug()<<"平滑曲线";
        }
        else
            {
            qDebug()<<"普通";
        }
    });
    connect(autoTimer,&QTimer::timeout,this,[=](){
        if(autoFlag) autoToZreoForce(5);
    });

}

testWidget::~testWidget()
{
    delete ui;
}
void testWidget::fresh(QList<float> decodeData)
{
    //0:S0力，10：S10计算位移,13：S13位移传感,29：时间
    test++;

    currentForce = decodeData[0];
    ui->load->display(QString::number(currentForce,'f',2));

    currentStress = currentForce/MainWindow::myWorker->details.targetSize;
    ui->stress->display(QString::number(currentStress,'f',2));

    targetLength = decodeData[1];
    ui->displacement->display(QString::number(targetLength-MainWindow::myWorker->details.lengthZero,'f',4));

    currentLength = decodeData[2];
    ui->displacement_sensors->display(QString::number(currentLength-MainWindow::myWorker->details.factLengthZero,'f',4));

    currentStrain = currentLength/MainWindow::myWorker->details.targetSize;
    ui->strain->display(QString::number(currentStrain,'f',4));

    currentTime = decodeData[3];
    ui->Duration->display(QString::number(currentTime-startTime,'f',4));

    *force_time_Series<<QPointF(currentTime,currentForce);

    *length_time_Series<<QPointF(currentTime,currentLength);

    *force_length_Series<<QPointF(currentLength-MainWindow::myWorker->details.lengthZero,currentForce);

    *stress_strain_Series<<QPointF(currentStrain,currentStress);

    float tempForce = currentForce;
    float temptargetLength = targetLength-MainWindow::myWorker->details.lengthZero;
    float tempcurrentLength = currentLength-MainWindow::myWorker->details.factLengthZero;
    float tempTime = currentTime - startTime;

    QList<float> temp = {tempForce,temptargetLength,tempcurrentLength,tempTime};

    factData.append(temp);



    switch (checkWaveId) {
    case 1:
        if(!chart->series().isEmpty())
        {
            qDebug()<<chart->series().first();
            chart->removeSeries(force_time_Series);
            chart->removeSeries(length_time_Series);
            chart->removeSeries(force_length_Series);
            chart->removeSeries(stress_strain_Series);
        }
        qDebug()<<QPointF(currentTime,currentForce);
        chart->addSeries(force_time_Series);
        break;
    case 2:
        if(!chart->series().isEmpty())
        {
            chart->removeSeries(force_time_Series);
            chart->removeSeries(length_time_Series);
            chart->removeSeries(force_length_Series);
            chart->removeSeries(stress_strain_Series);
        }
        chart->addSeries(length_time_Series);
        break;
    case 3:
        if(!chart->series().isEmpty())
        {
            chart->removeSeries(force_time_Series);
            chart->removeSeries(length_time_Series);
            chart->removeSeries(force_length_Series);
            chart->removeSeries(stress_strain_Series);
        }
        chart->addSeries(force_length_Series);
        break;
    case 4:
        if(!chart->series().isEmpty())
        {
            chart->removeSeries(force_time_Series);
            chart->removeSeries(length_time_Series);
            chart->removeSeries(force_length_Series);
            chart->removeSeries(stress_strain_Series);
        }
        chart->addSeries(stress_strain_Series);
        break;
    default:
        break;
    }
    chart->createDefaultAxes();

}


void testWidget::drawer()
{
    if(!chart->series().isEmpty())chart->removeSeries(factSeries);
    chart->addSeries(factSeries);
    chart->legend()->hide();
    chart->createDefaultAxes();
}
void testWidget::autoToZreoForce(int targetForce)
{
    if(currentForce>targetForce)
    {
        MainWindow::myControler->openCircleControl(-50,3);
    }
    else if(currentForce<-targetForce)
    {
        MainWindow::myControler->openCircleControl(50,3);
    }
    else
    {
        MainWindow::myControler->openCircleControl_STOP(3);
    }

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

    force_time_Series->clear();
    length_time_Series->clear();
    force_length_Series->clear();

    factData.clear();

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

                StrongSaveTest(MainWindow::myWorker->details.filePath+"//temp"+MainWindow::myWorker->details.fileName.arg(QDateTime::currentDateTime().toString("yy_MM_dd+hh_mm_ss")));
                qDebug()<<"STOP!";
                mutiSaveTimer->stop();
                MainWindow::myControler->connectToControl("192.168.0.20",6000,1000);
            }
            tempflag = !tempflag;
            qDebug()<<tempflag;
        });
        mutiSaveTimer->start(1000);
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
        out<<"Force";
        out<<",";
        out<<"TargetLength";
        out<<",";
        out<<"FactLength";
        out<<",";
        out<<"Time";
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
    emit saved();
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
        out<<"TEP";
        int strLength = tcpClient::mutireadBuffer.length()/218;
        for(int i = 0;i<strLength;i++)
        {
            out<<tcpClient::mutireadBuffer.mid(i*218,218).toHex().toStdString().c_str();

        }

        labelFile.close();
    }

    qDebug()<<"保存成功！";
    emit saved();
}

void testWidget::on_setLengthZero_clicked()
{
    MainWindow::myWorker->details.lengthZero = targetLength;
    MainWindow::myWorker->details.factLengthZero = currentLength;
    qDebug()<<"zero:"<<targetLength<<currentLength;
}


void testWidget::on_saveTest_clicked()
{
    QString filePath  = MainWindow::myWorker->details.filePath+"/"+MainWindow::myWorker->details.fileName+".csv";
    qDebug()<<filePath;
    saveTest(filePath);
}


void testWidget::on_stopTest_clicked()
{
    MainWindow::myControler->openCircleControl_STOP(3);
    MainWindow::myControler->disconnectToControl();
    factSeries->clear();
}


void testWidget::on_clearTest_clicked()
{
    factData.clear();
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
    StrongSaveTest(MainWindow::myWorker->details.filePath+"//temp"+MainWindow::myWorker->details.fileName);
}


void testWidget::on_mutiSaveOpen_toggled(bool checked)
{
    mutiSaveFlag = checked;

    if(mutiSaveFlag)
    {
        QMessageBox msgBox;
        msgBox.setText("警告：非必要不要用，严格按照说明执行本开关程序，否则可能会损坏机器！");
        msgBox.exec();
    }
    else
    {
        qDebug()<<"released";
    }

}


void testWidget::on_autoMove_toggled(bool checked)
{
    autoFlag = checked;
    if(!autoTimer->isActive())
    {
        MainWindow::myControler->channalClear(0);
        autoTimer->start(250);
    }
    if(!autoFlag)autoTimer->stop();

}

