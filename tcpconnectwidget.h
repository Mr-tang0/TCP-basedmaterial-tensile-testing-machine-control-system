#ifndef TCPCONNECTWIDGET_H
#define TCPCONNECTWIDGET_H

#include <QWidget>
#include "loginwidget.h"

namespace Ui {
class TcpConnectWidget;
}

class TcpConnectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpConnectWidget(QWidget *parent = nullptr);
    ~TcpConnectWidget();
    void commandLinkButton_clicked();
    loginWidget *login= new loginWidget;


private slots:
    void on_connect_Button_clicked();

    void on_disconnect_Button_clicked();

    void on_commandLinkButton_clicked();


private:
    Ui::TcpConnectWidget *ui;

};

#endif // TCPCONNECTWIDGET_H
