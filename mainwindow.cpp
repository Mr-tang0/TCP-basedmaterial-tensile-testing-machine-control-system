#include "mainwindow.h"
#include "ui_mainwindow.h"

Controler *MainWindow::myControler = new Controler;
worker *MainWindow::myWorker = new worker;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initThis();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initThis()
{
    QVBoxLayout *layout = new QVBoxLayout;
    delete ui->sonWidget->layout();

    layout->addWidget(test);
    layout->addWidget(system);
    layout->addWidget(newTest);

    ui->sonWidget->setLayout(layout);

    test->show();
    system->hide();
    newTest->hide();
    connect(newTest,&newTestWidget::thisHide,this,[=](){
        test->show();
        system->hide();
        newTest->hide();
    });

}

void MainWindow::on_portButton_clicked()
{
    myControler->connectToControl();
    connect(myControler,&Controler::decodeDone,test,&testWidget::fresh);//连接解码和界面
}


void MainWindow::on_actionNew_triggered()
{
    test->hide();
    system->hide();
    newTest->show();
}



