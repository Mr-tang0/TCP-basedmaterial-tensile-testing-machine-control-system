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
private slots:
    void on_Checked_clicked();
    void on_cancel_clicked();
};

#endif // SYSTEMSETWIDGET_H
