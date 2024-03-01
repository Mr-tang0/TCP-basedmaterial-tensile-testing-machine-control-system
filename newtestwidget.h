#ifndef NEWTESTWIDGET_H
#define NEWTESTWIDGET_H

#include <QWidget>
#include "includeHeader.h"


namespace Ui {
class newTestWidget;
}

class newTestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit newTestWidget(QWidget *parent = nullptr);
    ~newTestWidget();

private slots:
    void on_cancel_clicked();

private:
    Ui::newTestWidget *ui;
};

#endif // NEWTESTWIDGET_H
