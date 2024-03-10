#include "calculator.h"
#include "qdebug.h"
#include "ui_calculator.h"
#include<qmath.h>\

calculator::calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);

    connect(ui->buttonGroup_number,&QButtonGroup::idClicked,[=](int id){
        if(!pointflag)
        {
            if(abs(id+1)!=10) tempnumber = tempnumber*10+abs(id+1);
            else tempnumber = tempnumber*10;
            ui->lcdNumber->display(tempnumber);
        }else{
            if(abs(id+1)!=10)
            {
                tempnumber = tempnumber+abs(id+1)*pow(0.1,pos);
                ui->lcdNumber->display(tempnumber);
            }
            else
            {
                ui->lcdNumber->display(tempnumber);
            }
            pos++;

        }

    });

    connect(ui->Button_point,&QPushButton::clicked,[=](){
        pointflag = true;
    });

    connect(ui->buttonGroup_sign,&QButtonGroup::idClicked,[=](int id){
        qDebug()<<abs(id);
        switch (abs(id)) {
        case 4:
            signflag = 1;
            break;

        case 3:
            signflag = 2;
            break;
        case 2:
            signflag = 3;
            break;
        case 5:
            signflag = 4;
            break;
        default:
            break;
        }
        number1 = ui->lcdNumber->value();
        tempnumber = 0;
        pointflag = false;
        ui->lcdNumber->display(tempnumber);
        pos = 1;
        minus = false;
    });

}

calculator::~calculator()
{
    delete ui;
}



void calculator::on_Button_13_clicked()
{
    number2 = ui->lcdNumber->value();
    qDebug()<<number1<<number2<<signflag;
    switch (signflag) {
    case 1:
        ui->lcdNumber->display(number1+number2);
        break;
    case 2:
        ui->lcdNumber->display(number1-number2);
        break;
    case 3:
        ui->lcdNumber->display(number1*number2);
        break;
    case 4:
        ui->lcdNumber->display(number1/number2);
        break;
    default:
        break;
    }
}


void calculator::on_Button_AC_clicked()
{
    ui->lcdNumber->display(0);
    tempnumber = 0;
}


void calculator::on_Button_delete_clicked()
{

}


void calculator::on_Button_minus_clicked()
{
    minus = true;
    ui->lcdNumber->display(-(ui->lcdNumber->value()));
    tempnumber = ui->lcdNumber->value();
}

