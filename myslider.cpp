#include "myslider.h"
#include "ui_myslider.h"

mySlider::mySlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mySlider)
{
    ui->setupUi(this);
}

mySlider::~mySlider()
{
    delete ui;
}
