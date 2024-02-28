#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug()<<myClient->getNetWorkIP();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    myClient->tcpConnect("192.168.21.34",8080);
    connect(myClient,&tcpClient::readSomeMessage,[=](QByteArray message){
        qDebug()<<message;
    });
}


void MainWindow::on_pushButton_2_clicked()
{
    QString message =  ui->lineEdit->text();
    myClient->sendMessage(message.toUtf8());
}

