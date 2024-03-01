#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "includeHeader.h"
#include "controler.h"

namespace Ui {
class testWidget;
}

class testWidget : public QWidget
{
    Q_OBJECT

public:
    explicit testWidget(QWidget *parent = nullptr);
    ~testWidget();
    Controler *myControler = new Controler;

public slots:
    void fresh(QList<float> decodeData);

private slots:
    void on_pushButton_clicked();

    void on_up_clicked();

    void on_stop_clicked();

    void on_down_clicked();

    void on_startTest_clicked();

private:
    Ui::testWidget *ui;
};

#endif // TESTWIDGET_H
