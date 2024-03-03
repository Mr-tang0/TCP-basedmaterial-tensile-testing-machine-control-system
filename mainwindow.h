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

private:
    Ui::MainWindow *ui;

    testWidget *test = new testWidget;
    systemSetWidget *system = new systemSetWidget;
    newTestWidget *newTest = new newTestWidget;

    QtMaterialSnackbar  *const m_snackbar;
    QtMaterialDrawer *const m_drawer;
};
#endif // MAINWINDOW_H
