#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialdrawer.h>
#include "calculator.h"

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
    m_snackbar->setFont(QFont("幼圆"));

    m_drawer->setParent(ui->maiWidget);
    m_drawer->setClickOutsideToClose(true);
    m_drawer->setOverlayMode(true);

    QVBoxLayout *drawerLayout = new QVBoxLayout;
    m_drawer->setDrawerLayout(drawerLayout);
    drawerLayout->addWidget(mytcp);


    initThis();
    this->setWindowTitle("材料试验机");
    this->setWindowIcon(QIcon(":/new/prefix1/icon.png"));
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
    connect(system,&systemSetWidget::thisHide,this,[=](){
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

    connect(test,&testWidget::saved,this,[=](){
        m_snackbar->addMessage("保存成功!");
    });
    connect(test,&testWidget::failed,this,[=](){
        m_snackbar->addMessage("保存失败!");
    });
    connect(test,&testWidget::clear,this,[=](){
        m_snackbar->addMessage("已清除!");
    });
    // connect(TcpConnectWidget::login,&loginWidget::thisHide,this,[=](){this->show();});
    // connect(TcpConnectWidget::login,&loginWidget::thisShow,this,[=](){this->hide();});


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

        decodeThread *readFileDecode = new decodeThread;

        connect(readFileDecode,&decodeThread::decodeDone,test,&testWidget::fresh);//连接解码和界面

        if(fileData.mid(0,3)=="TEP")
        {
            QFileInfo fileinfo(filePath);
            myWorker->details.filePath = fileinfo.absolutePath();

            myWorker->details.fileName = fileinfo.fileName().remove(0,5)+"_decode";


            fileData.remove(0,3);

            QString temp;
            QByteArray builtData;
            uchar byteValue ;



            QThread *readFilethread = new QThread;
            readFileDecode->moveToThread(readFilethread);

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
            readFileDecode->MutiThreaddecodeMessage(builtData,{0,10,13,29});

            readFilethread->start();
        }
        else
        {
            QString tempfile = fileData;
            tempfile.remove(tempfile.length()-1,1);
            readFileDecode->readFile(tempfile);
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


void MainWindow::on_actionSave_triggered()
{
    QString filePath  = myWorker->details.filePath+"/"+myWorker->details.fileName+".csv";
    qDebug()<<filePath;
    test->saveTest(filePath);
}


void MainWindow::on_action_login_triggered()
{
    mytcp->commandLinkButton_clicked();
    // this->setEnabled(false);
}


void MainWindow::on_actionExit_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("提示");
    msgBox.setInformativeText("确认数据已保存?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {
        this->close();
    }


}


void MainWindow::on_actionsystem_triggered()
{
    test->hide();
    system->show();
    newTest->hide();
}


void MainWindow::on_actioncalculator_triggered()
{
    calculator *mycalculator =new calculator;
    mycalculator->show();
}

