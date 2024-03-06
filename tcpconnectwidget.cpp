#include "tcpconnectwidget.h"
#include "ui_tcpconnectwidget.h"
#include "mainwindow.h"

TcpConnectWidget::TcpConnectWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpConnectWidget)
{
    ui->setupUi(this);

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

