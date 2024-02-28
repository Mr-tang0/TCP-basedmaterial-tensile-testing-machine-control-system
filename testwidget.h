#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

namespace Ui {
class testWidget;
}

class testWidget : public QWidget
{
    Q_OBJECT

public:
    explicit testWidget(QWidget *parent = nullptr);
    ~testWidget();

private:
    Ui::testWidget *ui;
};

#endif // TESTWIDGET_H
