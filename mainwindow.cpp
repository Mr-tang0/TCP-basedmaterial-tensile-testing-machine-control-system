#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
    // ,m_snackbar(new QtMaterialSnackbar)
{
    ui->setupUi(this);
    // m_snackbar->setParent(this);
    // qDebug()<<myClient->getNetWorkIP();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    myClient->tcpConnect("192.168.21.34",8080);
    connect(myClient,&tcpClient::readSomeMessage,[=](QByteArray message){
        // m_snackbar->addMessage(message);
    });
}


void MainWindow::on_pushButton_2_clicked()
{
    QString message =  ui->lineEdit->text();
    myMotor->open(*myClient->mySocket);
}

