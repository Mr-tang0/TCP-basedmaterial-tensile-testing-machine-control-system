#include "newtestwidget.h"
#include "ui_newtestwidget.h"

newTestWidget::newTestWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::newTestWidget)
{
    ui->setupUi(this);
}

newTestWidget::~newTestWidget()
{
    delete ui;
}

void newTestWidget::on_cancel_clicked()
{
    this->hide();
}

