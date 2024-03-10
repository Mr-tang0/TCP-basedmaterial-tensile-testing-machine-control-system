#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.h"
#include "controler.h"
#include "includeHeader.h"
#include "testwidget.h"
#include "newtestwidget.h"
#include "systemsetwidget.h"
#include "worker.h"
#include"decodethread.h"
#include "tcpconnectwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QtMaterialDrawer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static Controler *myControler;
    static worker *myWorker;
    void initThis();

private slots:   
    void on_portButton_clicked();

    void on_actionNew_triggered();

    void on_TCP_actionn_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_action_login_triggered();

    void on_actionExit_triggered();

    void on_actionsystem_triggered();

    void on_actioncalculator_triggered();

private:
    Ui::MainWindow *ui;
    TcpConnectWidget *mytcp =new TcpConnectWidget;

    testWidget *test = new testWidget;
    systemSetWidget *system = new systemSetWidget;
    newTestWidget *newTest = new newTestWidget;

    QtMaterialSnackbar  *const m_snackbar;
    QtMaterialDrawer *const m_drawer;
    void delay(int delayTime);
    int temp_ = 0;

protected:
    void closeEvent(QCloseEvent *event)
    {
        QMessageBox msgBox;
        msgBox.setText("提示");
        msgBox.setInformativeText("确认数据已保存?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            event->accept();
        }else{
            event->ignore();
        }
    }
};
#endif // MAINWINDOW_H
