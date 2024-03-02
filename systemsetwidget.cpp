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
