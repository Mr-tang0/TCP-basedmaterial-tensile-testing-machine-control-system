#ifndef MYLCDNUMBER_H
#define MYLCDNUMBER_H

#include <QLCDNumber>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
class myLcdNumber : public QLCDNumber
{
    Q_OBJECT
public:
    myLcdNumber(QWidget *parent = nullptr);
    myLcdNumber();

signals:
    void doubleClicked();

protected:
    bool event(QEvent *event) override
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            emit doubleClicked();
            return true;
        }
        return QLCDNumber::event(event);
    }
};

#endif // MYLCDNUMBER_H
