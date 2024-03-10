#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "includeHeader.h"
#include <QColorDialog>
#include <qtmaterialtextfield.h>
#include <QKeyEvent>

namespace Ui {
class loginWidget;
}

class loginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit loginWidget(QWidget *parent = nullptr);
    ~loginWidget();

private slots:
    void on_loginBtn_clicked();

    void on_signUpBtn_clicked();

private:
    Ui::loginWidget *ui;
    QtMaterialSnackbar  *const m_snackbar;
    QtMaterialTextField  *const m_textField;

    bool logined(QString userName,QString password);
    bool signup(QString userName,QString password);
    void delay(int delayTime);
    QJsonObject loginObject;
    QByteArray hashEncode(QString data);


signals:
    void shortPassword();
    void login(QString userName);
    void unlogin();
    void thisShow();
    void thisHide();

protected:
    void keyPressEvent(QKeyEvent *event)
    {
        switch (event->key()) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            {
                on_loginBtn_clicked();
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





};

#endif // LOGINWIDGET_H
