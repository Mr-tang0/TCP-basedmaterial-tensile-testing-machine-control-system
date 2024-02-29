#ifndef SYSTEMSETWIDGET_H
#define SYSTEMSETWIDGET_H

#include <QWidget>

namespace Ui {
class systemSetWidget;
}

class systemSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit systemSetWidget(QWidget *parent = nullptr);
    ~systemSetWidget();

private:
    Ui::systemSetWidget *ui;
};

#endif // SYSTEMSETWIDGET_H
