#include "loginwidget.h"
#include "ui_loginwidget.h"

loginWidget::loginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginWidget),
    m_snackbar(new QtMaterialSnackbar),
    m_textField(new QtMaterialTextField)
{
    ui->setupUi(this);
    m_snackbar->setParent(this);
    m_snackbar->setFont(QFont("幼圆"));

    this->setWindowTitle("登录与注册");
    this->setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    ui->userName->setLabel("userName");
    ui->passWord->setLabel("passWord");

    this->setWindowFlags(Qt::CustomizeWindowHint);

    QString rootPath  = QCoreApplication::applicationDirPath();

    QFile file(rootPath+"/users.users");

    if(!file.open(QIODevice::ReadOnly))
    {
        QJsonDocument jsonDoc(loginObject);
        QString temp  = jsonDoc.toJson();
        file.open(QIODevice::WriteOnly);
        file.write(temp.toUtf8());
    }
    else
    {
        QByteArray jsonData = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        loginObject = jsonDoc.object();

    }
    file.close();

}

loginWidget::~loginWidget()
{
    delete ui;
}

void loginWidget::on_loginBtn_clicked()
{
    QString userName = ui->userName->text();
    QString password = ui->passWord->text();
    if(password.length()<6)
    {
        //密码过短
        m_snackbar->addMessage("密码不少于6位");
        emit shortPassword();
    }else{
        if(logined(userName,password)){
            m_snackbar->addMessage("登录成功");
            delay(1500);
            emit login(userName);
            this->hide();
            ui->passWord->text().clear();
        }
        else{
            //错误
            m_snackbar->addMessage("登录失败");
            emit unlogin();
        }
    }
}

void loginWidget::on_signUpBtn_clicked()
{
    QString userName = ui->userName->text();
    QString password = ui->passWord->text();
    if(password.length()<6)
    {
        //密码过短
        m_snackbar->addMessage("密码不少于6位");
        emit shortPassword();
    }else{
        if(signup(userName,password)){
            m_snackbar->addMessage("注册成功");
            delay(1500);
            emit login(userName);
            this->hide();
            ui->passWord->text().clear();
        }
        else{
            //错误
            m_snackbar->addMessage("用户已存在!");
            emit unlogin();
        }
    }
}


bool loginWidget::logined(QString userName,QString password)
{
    qDebug()<<loginObject[userName].toString()<<hashEncode(password).toHex();
    if(loginObject[userName].toString()==hashEncode(password).toHex())
    {
        return true;
    }else{
        return false;
    }
}

bool loginWidget::signup(QString userName,QString password)
{
    QString rootPath  = QCoreApplication::applicationDirPath();
    QFile file(rootPath+"/users.users");

    // QJsonObject loginObject;

    if(!loginObject[userName].isNull())
    {
        return false;
    }
    else
    {

        QString hashPassword = hashEncode(password).toHex();
        loginObject[userName] = hashPassword;

        QJsonDocument jsonDoc;
        jsonDoc.setObject(loginObject);
        QString temp  = jsonDoc.toJson();

        file.open(QIODevice::WriteOnly);
        file.write(temp.toUtf8());
        file.close();

        emit login(userName);
        return true;
    }


}

void loginWidget::delay(int delayTime)
{
    QEventLoop loop;
    QTimer::singleShot(delayTime,&loop,SLOT(quit()));
    loop.exec();

}

QByteArray loginWidget::hashEncode(QString data)
{
    QByteArray temp = data.toUtf8();
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(temp);
    QByteArray result = hash.result();
    return result;
}
