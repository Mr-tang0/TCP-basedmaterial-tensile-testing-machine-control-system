#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialdrawer.h>
#include "tcpconnectwidget.h"

Controler *MainWindow::myControler = new Controler;
worker *MainWindow::myWorker = new worker;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_snackbar(new QtMaterialSnackbar),
    m_drawer(new QtMaterialDrawer)
{
    ui->setupUi(this);
    m_snackbar->setParent(this);
    m_drawer->setParent(ui->maiWidget);
    m_drawer->setClickOutsideToClose(true);
    m_drawer->setOverlayMode(true);

    QVBoxLayout *drawerLayout = new QVBoxLayout;
    m_drawer->setDrawerLayout(drawerLayout);
    drawerLayout->addWidget(new TcpConnectWidget);


    initThis();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initThis()
{
    QVBoxLayout *layout = new QVBoxLayout;
    delete ui->sonWidget->layout();

    layout->addWidget(test);
    layout->addWidget(system);
    layout->addWidget(newTest);

    ui->sonWidget->setLayout(layout);

    test->show();
    system->hide();
    newTest->hide();
    connect(newTest,&newTestWidget::thisHide,this,[=](){
        test->show();
        system->hide();
        newTest->hide();
    });


    connect(Controler::myClient,&tcpClient::connected,this,[=](){
        m_snackbar->addMessage("connected!");
    });
    connect(Controler::myClient,&tcpClient::disconnected,this,[=](){
        m_snackbar->addMessage("disconnected!");
    });
    connect(myControler,&Controler::decodeDone,test,&testWidget::fresh);//连接解码和界面

}

void MainWindow::on_portButton_clicked()
{
    m_drawer->openDrawer();
}


void MainWindow::on_actionNew_triggered()
{
    test->hide();
    system->hide();
    newTest->show();
}





void MainWindow::on_TCP_actionn_triggered()
{
    on_portButton_clicked();
}

