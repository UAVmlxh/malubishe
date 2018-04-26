#include "widget.h"
#include "ui_widget.h"
#define MAXConnect 10 //最大的连接数目

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpServer=new QTcpServer(this);  //初始化服务器指针
    myPort=17892;
    //方法二：手动设置IP地址
    myAddress="127.0.0.1";

    /**********步骤二：绑定端口和IP地址，开始监听端口***********************************/
   if(tcpServer->listen(QHostAddress(myAddress),myPort))  //绑定IP和端口
   {

   }
   else
   {

   }

   tcpServer->setMaxPendingConnections(MAXConnect);  //设置最大的绑定数目为10

   connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnectionSlot()));

   ui->btnUser->setEnabled(false);
   ui->btnGuest->setEnabled(false);
   ui->btnEnsure->setEnabled(false);

   connect(&myEnsure,SIGNAL(ensureOperate(QString)),this,SLOT(ensureOperateSlot(QString)));
   connect(&myEnsure,SIGNAL(exitFromEnsureForm()),this,SLOT(exitFromEnsureFormSlot()));
   this->update();
}

Widget::~Widget()
{
    delete ui;
}

//客户端连接上的信号
void Widget::newConnectionSlot()
{
    tcpClient=tcpServer->nextPendingConnection(); //连接对象
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readyReadSlot()));  //关联读信息的槽函数
    ui->btnUser->setEnabled(true);
    ui->btnGuest->setEnabled(true);
    ui->btnEnsure->setEnabled(true);
    this->setWindowTitle(tr("佩奇社区"));
}


//客户端接收消息信号
void Widget::readyReadSlot()
{
    QTcpSocket *client=(QTcpSocket *)this->sender();
    static int count=3;
    QString readData=client->readAll();
    //认证成功
    if(readData.mid(0,4)==QString("1201"))
    {
           QMessageBox::information(this,tr(" "),tr("欢迎回家"));
           count=3;
    }
    else if(readData.mid(0,4)==QString("1202")) //认证失败
    {

            if((count<=3)&&(count>0))
            {
                count--;
                QString  s="密码输入错误,还有";
                s.append(QString::number(count));
                s.append("次机会");
                QMessageBox::information(this,tr(" "),s);
            }
            else
            {
                count=3;
                QMessageBox::information(this,tr(" "),tr("卡片锁死,请尽快去小区保卫室解锁"));
            }
    }
    else if(readData.mid(0,4)==QString("1208"))  //来宾卡
    {
        QString  s="来宾卡剩余";
        s.append(readData.mid(5,1));
        s.append("次使用机会");
         QMessageBox::information(this,tr(" "),tr("欢迎来宾"),s);
    }
    else if(readData.mid(0,4)==QString("1209"))  //非小区授权卡
    {
        QMessageBox::information(this,tr(" "),tr("非小区授权卡"));
    }
    else if(readData.mid(0,4)==QString("1207"))  //卡片锁死
    {
        QMessageBox::information(this,tr(" "),tr("卡片锁死,请尽快去小区保卫室解锁"));
    }
    else if(readData.mid(0,2)==QString("13"))  //卡片锁死
    {
        QMessageBox::information(this,tr(" "),tr("来宾卡错误"));
    }
    //保安界面的信息
    else if(readData.mid(0,4)==QString("2201"))
    {
        //解锁成功
        myEnsure.sendDataToEnsureForm(QString("unlock"),true);
    }
    else if(readData.mid(0,4)==QString("2202"))
    {
        //解锁失败
        myEnsure.sendDataToEnsureForm(QString("unlock"),false);
    }
    //查看密码
    else if(readData.mid(0,2)==QString("33"))
    {
        myEnsure.sendDataToEnsureForm(QString("show")+readData.mid(2,6),true);
    }
    else if(readData.mid(0,2)==QString("34"))
    {
        myEnsure.sendDataToEnsureForm(QString("show"),false);
    }
    else if(readData.mid(0,2)==QString("55"))  //    //来宾卡结果
    {
        //添加来宾卡成功
        myEnsure.sendDataToEnsureForm(QString("addGuest"),true);

    }
    else if(readData.mid(0,2)==QString("56"))
    {
        //添加来宾卡失败
        myEnsure.sendDataToEnsureForm(QString("addGuest"),false);
    }
     else if(readData.mid(0,2)==QString("66"))     //用户卡结果
    {
        myEnsure.sendDataToEnsureForm(QString("addUser"),true);
    }
    else if(readData.mid(0,2)==QString("67"))
    {
        myEnsure.sendDataToEnsureForm(QString("addUser"),false);
    }
    else if(readData.mid(0,4)==QString("4401")) //修改密码成功
    {
        myEnsure.sendDataToEnsureForm(QString("ch"),true);
    }
    else if(readData.mid(0,2)==QString("45")) //修改密码失败
    {
        myEnsure.sendDataToEnsureForm(QString("ch"),false);
    }
}

void Widget::on_btnUser_clicked()
{
     QString userPasswd=QInputDialog::getText(this,tr("密码"),tr("请输入密码:"),QLineEdit::Password);
      if(!userPasswd.isEmpty())
      {
            if(userPasswd.count()!=6)
            {
                QMessageBox::warning(this,tr(" "),tr("密码输入错误，请核对后输入"));
                return;
            }
            userPasswd.prepend("12");
            tcpClient->write(userPasswd.toLatin1()); //发送数据
      }
      qDebug()<<userPasswd;
}

void Widget::on_btnGuest_clicked()
{
      QString guest="13aaaaaa";
      tcpClient->write(guest.toLatin1()); //发送数据
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/image/test.jpg"));
}

//保安界面
void Widget::on_btnEnsure_clicked()
{
     QString ensurePasswd=QInputDialog::getText(this,tr("密码"),tr("请输入密码:"),QLineEdit::Password);
     if(!ensurePasswd.isEmpty())
     {
         if(ensurePasswd.count()==6)
         {
                if(ensurePasswd==QString("123456"))
                {
                    myEnsure.show();
                    this->hide();
                }
         }
         else
         {
             QMessageBox::warning(this,tr(" "),tr("密码输入错误，请核对后输入"));
             return;
         }
     }
}

void Widget::ensureOperateSlot(QString opt)
{
    QString sendData;
    if(opt=="show")
    {
        sendData="33000000";
        tcpClient->write(sendData.toLatin1()); //发送数据
    }
    else if(opt=="unlock")
    {
        sendData="22000000";
        tcpClient->write(sendData.toLatin1()); //发送数据
    }
    else if(opt.mid(0,2)=="ch")
    {
        sendData="44"+opt.mid(2,6);
        tcpClient->write(sendData.toLatin1()); //发送数据
    }
    //添加用户
    else if(opt=="addGuest")
    {
        sendData="55000000";
        tcpClient->write(sendData.toLatin1()); //发送数据
    }
    else if(opt=="addUser")
    {
        sendData="66000000";
        tcpClient->write(sendData.toLatin1()); //发送数据
    }
    qDebug()<<opt<<"  "<<sendData;
}

void Widget::exitFromEnsureFormSlot()
{
    this->show();
}
