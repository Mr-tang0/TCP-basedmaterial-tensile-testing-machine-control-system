#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpclient.h"
#include "controler.h"
#include "includeHeader.h"


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
    void on_portBottom_clicked();

private:
    Ui::MainWindow *ui;
    // QtMaterialSnackbar  *const m_snackbar;
};
#endif // MAINWINDOW_H
