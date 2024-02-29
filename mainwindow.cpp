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


    systemSetWidget *system = new systemSetWidget;
    testWidget *test = new testWidget;

    QVBoxLayout *layout = new QVBoxLayout;
    delete ui->sonWidget->layout();

    layout->addWidget(test);
    ui->sonWidget->setLayout(layout);
    test->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_portBottom_clicked()
{

    myClient->details.netWorkIP = "192.168.0.20";
    myClient->details.portNumber = 6000;
    myClient->details.sampleRate = 20;

    myClient->tcpConnect();

    connect(myClient,&tcpClient::readSomeMessage,[=](TCPFrame messageFrame){
        decodeThread decode;
        // ui->lcdNumber->display(decode.dataToFloat(messageFrame.data[0]));
    });
}

