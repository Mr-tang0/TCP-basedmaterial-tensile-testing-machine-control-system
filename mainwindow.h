#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.h"
#include "controler.h"
#include "includeHeader.h"
#include "testwidget.h"
#include "newtestwidget.h"
#include "systemsetwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static tcpClient *myClient;
    static Controler *myControler;

private slots:   
    void on_portButton_clicked();

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    void initThis();

    testWidget *test = new testWidget;

    systemSetWidget *system = new systemSetWidget;
    newTestWidget *newTest = new newTestWidget;
    // QtMaterialSnackbar  *const m_snackbar;
};
#endif // MAINWINDOW_H
