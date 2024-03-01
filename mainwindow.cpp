#include "mainwindow.h"192
#include "ui_mainwindow.h"

#include"decodethread.h"

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
    QVBoxLayout *layout = new QVBoxLayout;
    delete ui->sonWidget->layout();

    layout->addWidget(test);
    layout->addWidget(system);
    layout->addWidget(newTest);

    ui->sonWidget->setLayout(layout);

    test->show();
    system->hide();
    newTest->hide();

}

void MainWindow::on_portButton_clicked()
{
    myClient->details.netWorkIP = "192.168.0.20";
    myClient->details.portNumber = 6000;
    myClient->details.sampleRate = 20;

    myClient->tcpConnect();
    connect(myClient,&tcpClient::decodeDone,test,&testWidget::fresh);
}


void MainWindow::on_actionNew_triggered()
{
    test->hide();
    system->hide();
    newTest->show();
}

