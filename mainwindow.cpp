#include "mainwindow.h"192
#include "ui_mainwindow.h"
#include "systemsetwidget.h"
#include"decodethread.h"
#include "testwidget.h"

tcpClient *MainWindow::myClient = new tcpClient;
Controler *MainWindow::myControler = new Controler;


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
    systemSetWidget *system = new systemSetWidget;
    testWidget *test = new testWidget;

    QVBoxLayout *layout = new QVBoxLayout;
    delete ui->sonWidget->layout();

    layout->addWidget(test);
    layout->addWidget(system);


    ui->sonWidget->setLayout(layout);

    test->show();
    system->hide();



}


void MainWindow::on_portBottom_clicked()
{

    myClient->details.netWorkIP = "192.168.0.20";
    myClient->details.portNumber = 6000;
    myClient->details.sampleRate = 20;

    myClient->tcpConnect();

}


void MainWindow::on_portButton_clicked()
{
    ui->portButton->raise();
    ui->portButton->move(100,100);
}

