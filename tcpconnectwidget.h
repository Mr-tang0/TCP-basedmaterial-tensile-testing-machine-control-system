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

private slots:
    void on_connect_Button_clicked();

    void on_disconnect_Button_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::TcpConnectWidget *ui;
    loginWidget *login = new loginWidget;
};

#endif // TCPCONNECTWIDGET_H
