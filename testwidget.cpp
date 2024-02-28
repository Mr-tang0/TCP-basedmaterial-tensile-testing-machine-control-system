#include "testwidget.h"
#include "ui_testwidget.h"

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
