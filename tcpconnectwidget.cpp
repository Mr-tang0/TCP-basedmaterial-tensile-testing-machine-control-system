#include "tcpconnectwidget.h"
#include "ui_tcpconnectwidget.h"
#include "mainwindow.h"


TcpConnectWidget::TcpConnectWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpConnectWidget)
{
    ui->setupUi(this);
    ui->UserName->setText(MainWindow::myWorker->details.UseName);

    // ui->connect_Button->setEnabled(false);
    connect(login,&loginWidget::login,this,[=](QString userName){
        MainWindow::myWorker->details.UseName = userName;
        ui->UserName->setText(MainWindow::myWorker->details.UseName);
        ui->connect_Button->setEnabled(true);
    });

}

TcpConnectWidget::~TcpConnectWidget()
{
    delete ui;
}

void TcpConnectWidget::on_connect_Button_clicked()
{
    MainWindow::myControler->connectToControl(ui->TcpIP->text(),ui->Port->text().toInt(),1000);
}


void TcpConnectWidget::on_disconnect_Button_clicked()
{
    MainWindow::myControler->disconnectToControl();
}

void TcpConnectWidget::commandLinkButton_clicked()
{
    on_commandLinkButton_clicked();
}
void TcpConnectWidget::on_commandLinkButton_clicked()
{
    //登录注册
    qDebug()<<"click";
    login->show();
}

