#include "form.h"
#include "ui_form.h"



Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->update();
}

Form::~Form()
{
    delete ui;
}

void  Form::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/image/baoan.jpg"));
}
//查看密码
void Form::on_btnShow_clicked()
{
    emit ensureOperate("show");
}

//解锁密码
void Form::on_btnUnlcok_clicked()
{
    emit ensureOperate("unlock");
}

//修改密码
void Form::on_btnChange_clicked()
{
    QString passwd=QInputDialog::getText(this,tr("密码"),tr("请输入密码:"),QLineEdit::Password);
    if(!passwd.isEmpty())
    {
        if(passwd.count()==6)
        {
                emit ensureOperate("ch"+passwd);
        }
        else
        {
            QMessageBox::warning(this,tr(" "),tr("密码输入错误，请核对后输入"));
            return;
        }
    }
}

//接收数据的处理
void Form::sendDataToEnsureForm(QString what,bool isSuccessful)
{
    if(what==QString("unlock"))
    {
        if(isSuccessful)
        {
            QMessageBox::warning(this,tr(" "),tr("密码解锁成功"));
            return;
        }
        else
        {
            QMessageBox::warning(this,tr(" "),tr("密码解锁失败"));
            return;
        }
    }
    else if(what.mid(0,4)==QString("show"))
    {
        if(isSuccessful)
        {
        QString s="密码为:";
        s.append(what.mid(4,6));
        QMessageBox::warning(this,tr("查看密码"),s);
        return;
        }
        else
        {
        QMessageBox::warning(this,tr("查看密码"),tr("卡片锁死,请解锁后查看"));
        }
    }
    else if(what==QString("addGuest"))
    {
        if(isSuccessful)
        {
            QMessageBox::information(this,tr("添加来宾"),tr("添加来宾成功"));
            return;
        }
        else
        {
            QMessageBox::information(this,tr("添加来宾"),tr("添加来宾失败"));
            return;
        }
    }
    else if(what==QString("addUser"))
    {
        if(isSuccessful)
        {
            QMessageBox::information(this,tr("添加用户"),tr("添加用户成功"));
            return;
        }
        else
        {
            QMessageBox::information(this,tr("添加用户"),tr("添加用户失败"));
            return;
        }
    }
    else if(what==QString("ch"))
    {
        if(isSuccessful)
        {
            QMessageBox::information(this,tr("修改密码"),tr("修改密码成功"));
        }
        else
        {
            QMessageBox::information(this,tr("修改密码"),tr("修改密码失败"));
        }
    }
}

void Form::on_addUser_clicked()
{
    emit ensureOperate("addUser");
}

void Form::on_btnAddGuest_clicked()
{
    emit ensureOperate("addGuest");
}

void Form::on_btnExit_clicked()
{
    this->hide();
    emit exitFromEnsureForm();
}
