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
        m_snackbar->addMessage("连接成功!");
    });
    connect(Controler::myClient,&tcpClient::disconnected,this,[=](){
        m_snackbar->addMessage("异常断开!");
    });
    connect(myControler,&Controler::decodeDone,test,&testWidget::fresh);//连接解码和界面

    connect(test,&testWidget::saved,[=](){
        m_snackbar->addMessage("保存成功!");
    });

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

        QByteArray fileData = labelFile.readAll();
        labelFile.close();

        decodeThread *decode = new decodeThread;
        connect(decode,&decodeThread::decodeDone,test,&testWidget::fresh);//连接解码和界面
        if(fileData.mid(0,3)=="TEP")
        {
            fileData.remove(0,3);

            QString temp;
            QByteArray builtData;
            uchar byteValue ;



            QThread *thread = new QThread;
            decode->moveToThread(thread);

            int needDecodeLength = fileData.length()/436;

            QStringList dataFrame;
            for (int i = 0; i < int(needDecodeLength/100); ++i) {
                dataFrame.append(fileData.mid(i*100*436,100*436));
            }
            dataFrame.append(fileData.right(fileData.length()-int(needDecodeLength/100)*100*436));



            foreach (QString item, dataFrame) {
                for (int i = 0; i < 100*436; ++i) {
                    temp = temp + " "+ item.mid(i*2,2);
                }
                temp.remove(0,1);


                bool ok;
                for (const auto &chunk : temp.split(" "))
                {
                    if(chunk!="")
                    {
                        byteValue = uchar(chunk.toUShort(&ok, 16));
                        if (!ok)
                        {
                            qDebug() << "数据存在错误" ;
                        }
                        else
                        {
                            builtData.append(char(byteValue));
                        }
                    }
                    temp_++;
                }
                temp.clear();
                delay(0);
            }
            decode->MutiThreaddecodeMessage(builtData,{0,10,13,29});

            thread->start();
        }
        else
        {
            QString tempfile = fileData;
            tempfile.remove(tempfile.length()-1,1);
            decode->readFile(tempfile);
        }



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
