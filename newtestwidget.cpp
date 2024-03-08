#include "newtestwidget.h"
#include "ui_newtestwidget.h"
#include "mainwindow.h"

newTestWidget::newTestWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::newTestWidget)
{
    ui->setupUi(this);

    connect(this,&newTestWidget::thisShow,this,&newTestWidget::initThis);

    myRadioGroup->addButton(ui->fatigue_radioButton);
    myRadioGroup->addButton(ui->pull_radioButton);
    myRadioGroup->addButton(ui->push_radioButton);
    connect(myRadioGroup, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),this,[=](QAbstractButton *button){
        if(button->text()=="疲劳"){
            ui->testTypeManu_stackedWidget->setCurrentIndex(1);
        }else{
            ui->testTypeManu_stackedWidget->setCurrentIndex(0);
        }
    });
    connect(ui->stopAction_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this,[=](int index){
        QStringList temp = {"s","N","mm",""};
        ui->unit_label->setText(temp[index]);
        ui->stopActionValue_doubleSpinBox_12->setEnabled(true);
    });

}

newTestWidget::~newTestWidget()
{
    delete ui;
}

void newTestWidget::initThis()
{
    ui->userName_lineEidt->setText(MainWindow::myWorker->details.UseName);

    QString timeString = QDateTime::currentDateTime().toString("yy-MM-dd-hh:mm:ss");
    ui->time_lineEidt->setText(timeString);

}

void newTestWidget::on_cancel_clicked()
{
    this->hide();
}


void newTestWidget::on_Checked_clicked()
{
    //基础信息
    if(ui->userName_lineEidt->text()!="")MainWindow::myWorker->details.UseName = ui->userName_lineEidt->text();
    if(ui->number_lineEidt->text()!="")MainWindow::myWorker->details.Number = ui->number_lineEidt->text();
    MainWindow::myWorker->details.testTime = ui->time_lineEidt->text();
    MainWindow::myWorker->details.testType = myRadioGroup->checkedButton()->text();
    if(ui->filePath_lineEdit->text()!="")MainWindow::myWorker->details.filePath = ui->filePath_lineEdit->text();
    if(ui->filePath_lineEdit_2->text()!="")
        MainWindow::myWorker->details.fileName = ui->filePath_lineEdit_2->text();
    else
        MainWindow::myWorker->details.fileName = MainWindow::myWorker->details.UseName+MainWindow::myWorker->details.testTime;

    qDebug()<<MainWindow::myWorker->details.filePath;

    //压缩拉伸
    MainWindow::myWorker->details.speed = ui->speed_doubleSpinBox_2->value();
    MainWindow::myWorker->details.length = ui->length_doubleSpinBox->value();
    //疲劳
    MainWindow::myWorker->details.WaveTypeNumber = ui->waveType_comboBox->currentIndex()+1;

    MainWindow::myWorker->details.cycleSpeed = ui->cicleSpeed_doubleSpinBox_9->value();
    MainWindow::myWorker->details.cycleLength = ui->cycleLength_doubleSpinBox_8->value();
    MainWindow::myWorker->details.frequency = ui->circleFrequecy_doubleSpinBox_11->value();

    MainWindow::myWorker->details.cycleNumber = ui->circleNumber_spinBox->value();
    MainWindow::myWorker->details.stopAction = ui->stopAction_comboBox->currentIndex();
    MainWindow::myWorker->details.stopActionValue = ui->stopActionValue_doubleSpinBox_12->value();

    this->hide();
}


void newTestWidget::on_chooseFilePath_pushButton_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this,QStringLiteral("选择保存位置"));
    ui->filePath_lineEdit->setText(folderPath);
}

