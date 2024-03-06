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


void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,QStringLiteral("选择文件位置"));

    QFile labelFile(filePath);
    if(!labelFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"指定位置不存在!";
    }
    else {
        m_snackbar->addMessage("正在解码!");
        delay(2000);
        decodeThread *decode = new decodeThread;
        QThread *thread = new QThread;
        decode->moveToThread(thread);


        connect(decode,&decodeThread::decodeDone,test,&testWidget::fresh);//连接解码和界面

        thread->start();

        QByteArray fileData = labelFile.readAll();
        labelFile.close();

        QString temp_f,temp;
        QByteArray builtData;
        uchar byteValue ;

        for (int i = 0; i < fileData.length()/2; i++) {
            temp = temp+" "+fileData.mid(i*2,2);
            qDebug()<<i<<fileData.length()/2;
        }
        temp.remove(0,1);

        bool ok;
        for (const auto &chunk : temp.split(" "))
        {
            byteValue = uchar(chunk.toUShort(&ok, 16));
            if (!ok)
            {
                // 转换失败后的操作，待定
                qDebug() << "数据存在错误" ;
            }
            else
            {
                builtData.append(char(byteValue));
            }
            temp_++;
            qDebug()<<temp_;

        }
        temp.clear();
        decode->MutiThreaddecodeMessage(builtData,{0,10,29});

        // int length  = fileData.length()/436;
        // for (int j = 0; j < length; j++)
        // {
        //     temp_++;
        //     qDebug()<<fileData.length()/436;

        //     temp_f = fileData.left(436);
        //     fileData.remove(0,436);


        //     for (int i = 0; i < 218; i++) {
        //         temp = temp+" "+temp_f.mid(i*2,2);
        //     }

        //     temp.remove(0,1);


        //     bool ok;
        //     for (const auto &chunk : temp.split(" "))
        //     {
        //         byteValue = uchar(chunk.toUShort(&ok, 16));
        //         if (!ok)
        //         {
        //             // 转换失败后的操作，待定
        //             qDebug() << "数据存在错误" ;
        //         }
        //         else
        //         {
        //             builtData.append(char(byteValue));
        //         }

        //     }
        //     temp.clear();
        //     decode->MutiThreaddecodeMessage(builtData,{0,10,29});
        // }
        delay(1000);
        m_snackbar->addMessage("解码完成!");

    }


}
void MainWindow::delay(int delayTime)
{
    QEventLoop loop;
    QTimer::singleShot(delayTime,&loop,SLOT(quit()));
    loop.exec();

}
