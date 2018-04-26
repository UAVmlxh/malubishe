#include "widget.h"
#include "ui_widget.h"
#define MAXConnect 10 //����������Ŀ

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpServer=new QTcpServer(this);  //��ʼ��������ָ��
    myPort=17892;
    //���������ֶ�����IP��ַ
    myAddress="127.0.0.1";

    /**********��������󶨶˿ں�IP��ַ����ʼ�����˿�***********************************/
   if(tcpServer->listen(QHostAddress(myAddress),myPort))  //��IP�Ͷ˿�
   {

   }
   else
   {

   }

   tcpServer->setMaxPendingConnections(MAXConnect);  //�������İ���ĿΪ10

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

//�ͻ��������ϵ��ź�
void Widget::newConnectionSlot()
{
    tcpClient=tcpServer->nextPendingConnection(); //���Ӷ���
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readyReadSlot()));  //��������Ϣ�Ĳۺ���
    ui->btnUser->setEnabled(true);
    ui->btnGuest->setEnabled(true);
    ui->btnEnsure->setEnabled(true);
    this->setWindowTitle(tr("��������"));
}


//�ͻ��˽�����Ϣ�ź�
void Widget::readyReadSlot()
{
    QTcpSocket *client=(QTcpSocket *)this->sender();
    static int count=3;
    QString readData=client->readAll();
    //��֤�ɹ�
    if(readData.mid(0,4)==QString("1201"))
    {
           QMessageBox::information(this,tr(" "),tr("��ӭ�ؼ�"));
           count=3;
    }
    else if(readData.mid(0,4)==QString("1202")) //��֤ʧ��
    {

            if((count<=3)&&(count>0))
            {
                count--;
                QString  s="�����������,����";
                s.append(QString::number(count));
                s.append("�λ���");
                QMessageBox::information(this,tr(" "),s);
            }
            else
            {
                count=3;
                QMessageBox::information(this,tr(" "),tr("��Ƭ����,�뾡��ȥС�������ҽ���"));
            }
    }
    else if(readData.mid(0,4)==QString("1208"))  //������
    {
        QString  s="������ʣ��";
        s.append(readData.mid(5,1));
        s.append("��ʹ�û���");
         QMessageBox::information(this,tr(" "),tr("��ӭ����"),s);
    }
    else if(readData.mid(0,4)==QString("1209"))  //��С����Ȩ��
    {
        QMessageBox::information(this,tr(" "),tr("��С����Ȩ��"));
    }
    else if(readData.mid(0,4)==QString("1207"))  //��Ƭ����
    {
        QMessageBox::information(this,tr(" "),tr("��Ƭ����,�뾡��ȥС�������ҽ���"));
    }
    else if(readData.mid(0,2)==QString("13"))  //��Ƭ����
    {
        QMessageBox::information(this,tr(" "),tr("����������"));
    }
    //�����������Ϣ
    else if(readData.mid(0,4)==QString("2201"))
    {
        //�����ɹ�
        myEnsure.sendDataToEnsureForm(QString("unlock"),true);
    }
    else if(readData.mid(0,4)==QString("2202"))
    {
        //����ʧ��
        myEnsure.sendDataToEnsureForm(QString("unlock"),false);
    }
    //�鿴����
    else if(readData.mid(0,2)==QString("33"))
    {
        myEnsure.sendDataToEnsureForm(QString("show")+readData.mid(2,6),true);
    }
    else if(readData.mid(0,2)==QString("34"))
    {
        myEnsure.sendDataToEnsureForm(QString("show"),false);
    }
    else if(readData.mid(0,2)==QString("55"))  //    //���������
    {
        //����������ɹ�
        myEnsure.sendDataToEnsureForm(QString("addGuest"),true);

    }
    else if(readData.mid(0,2)==QString("56"))
    {
        //���������ʧ��
        myEnsure.sendDataToEnsureForm(QString("addGuest"),false);
    }
     else if(readData.mid(0,2)==QString("66"))     //�û������
    {
        myEnsure.sendDataToEnsureForm(QString("addUser"),true);
    }
    else if(readData.mid(0,2)==QString("67"))
    {
        myEnsure.sendDataToEnsureForm(QString("addUser"),false);
    }
    else if(readData.mid(0,4)==QString("4401")) //�޸�����ɹ�
    {
        myEnsure.sendDataToEnsureForm(QString("ch"),true);
    }
    else if(readData.mid(0,2)==QString("45")) //�޸�����ʧ��
    {
        myEnsure.sendDataToEnsureForm(QString("ch"),false);
    }
}

void Widget::on_btnUser_clicked()
{
     QString userPasswd=QInputDialog::getText(this,tr("����"),tr("����������:"),QLineEdit::Password);
      if(!userPasswd.isEmpty())
      {
            if(userPasswd.count()!=6)
            {
                QMessageBox::warning(this,tr(" "),tr("�������������˶Ժ�����"));
                return;
            }
            userPasswd.prepend("12");
            tcpClient->write(userPasswd.toLatin1()); //��������
      }
      qDebug()<<userPasswd;
}

void Widget::on_btnGuest_clicked()
{
      QString guest="13aaaaaa";
      tcpClient->write(guest.toLatin1()); //��������
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/image/test.jpg"));
}

//��������
void Widget::on_btnEnsure_clicked()
{
     QString ensurePasswd=QInputDialog::getText(this,tr("����"),tr("����������:"),QLineEdit::Password);
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
             QMessageBox::warning(this,tr(" "),tr("�������������˶Ժ�����"));
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
        tcpClient->write(sendData.toLatin1()); //��������
    }
    else if(opt=="unlock")
    {
        sendData="22000000";
        tcpClient->write(sendData.toLatin1()); //��������
    }
    else if(opt.mid(0,2)=="ch")
    {
        sendData="44"+opt.mid(2,6);
        tcpClient->write(sendData.toLatin1()); //��������
    }
    //����û�
    else if(opt=="addGuest")
    {
        sendData="55000000";
        tcpClient->write(sendData.toLatin1()); //��������
    }
    else if(opt=="addUser")
    {
        sendData="66000000";
        tcpClient->write(sendData.toLatin1()); //��������
    }
    qDebug()<<opt<<"  "<<sendData;
}

void Widget::exitFromEnsureFormSlot()
{
    this->show();
}
