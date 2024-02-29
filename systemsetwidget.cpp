#include "systemsetwidget.h"
#include "ui_systemsetwidget.h"
#include "mainwindow.h"

systemSetWidget::systemSetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::systemSetWidget)
{
    ui->setupUi(this);
    QStringList IPList = MainWindow::myClient->getNetWorkIP();
    foreach (QString ip, IPList) {
        // ui->portComboBox->addItem(ip);
    }
}

systemSetWidget::~systemSetWidget()
{
    delete ui;
}
