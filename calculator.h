#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include<QKeyEvent>

namespace Ui {
class calculator;
}

class calculator : public QWidget
{
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = nullptr);
    ~calculator();
    float tempnumber = 0;
    float number1 = 0;
    float number2 = 0;
    float number3 = 0;

    int signflag = 0;
    bool pointflag = false;
    bool minus = false;
    int pos = 1;

private slots:
    void on_Button_13_clicked();

    void on_Button_AC_clicked();

    void on_Button_delete_clicked();

    void on_Button_minus_clicked();

private:
    Ui::calculator *ui;

protected:
    void keyPressEvent(QKeyEvent *event)
    {
        switch (event->key()) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        {
            on_Button_13_clicked();
        }
        break;
        case Qt::Key_Escape:
        {
            this->hide();
        }
        break;

        default:
            break;
        }
    }
};

#endif // CALCULATOR_H
