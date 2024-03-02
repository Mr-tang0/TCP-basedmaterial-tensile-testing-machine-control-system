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
    void initThis();

private slots:
    void on_cancel_clicked();

    void on_Checked_clicked();

    void on_chooseFilePath_pushButton_clicked();

private:
    Ui::newTestWidget *ui;

    QButtonGroup *myRadioGroup = new QButtonGroup(this);
    void showEvent(QShowEvent*event)
    {
        emit thisShow();
        QWidget::showEvent(event);
    }
    void hideEvent(QHideEvent*event)
    {
        emit thisHide();
        QWidget::hideEvent(event);
    }

signals:
    void thisShow();
    void thisHide();
};

#endif // NEWTESTWIDGET_H
