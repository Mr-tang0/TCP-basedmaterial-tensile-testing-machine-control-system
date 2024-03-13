#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QWidget>

namespace Ui {
class mySlider;
}

class mySlider : public QWidget
{
    Q_OBJECT

public:
    explicit mySlider(QWidget *parent = nullptr);
    ~mySlider();

private:
    Ui::mySlider *ui;
};

#endif // MYSLIDER_H
