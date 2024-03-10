#include "systemsetwidget.h"
#include "ui_systemsetwidget.h"
#include "mainwindow.h"

systemSetWidget::systemSetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::systemSetWidget)
{
    ui->setupUi(this);

}

systemSetWidget::~systemSetWidget()
{
    delete ui;
}

void systemSetWidget::on_Checked_clicked()
{
    this->hide();
}


void systemSetWidget::on_cancel_clicked()
{
    this->hide();
}

