#include "testwidget.h"
#include "ui_testwidget.h"
#include"mainwindow.h"

testWidget::testWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::testWidget)
{
    ui->setupUi(this);
}

testWidget::~testWidget()
{
    delete ui;
}

void testWidget::on_pushButton_clicked()
{
    myControler->mode_Reciprocate(*MainWindow::myClient);
}


void testWidget::on_up_clicked()
{
    myControler->openCircleControl_UP(*MainWindow::myClient,3000,3);
}


void testWidget::on_stop_clicked()
{
    myControler->openCircleControl_UP(*MainWindow::myClient,0,3);
}


void testWidget::on_down_clicked()
{
    myControler->openCircleControl_DOWN(*MainWindow::myClient,3000,3);
}

