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
//�鿴����
void Form::on_btnShow_clicked()
{
    emit ensureOperate("show");
}

//��������
void Form::on_btnUnlcok_clicked()
{
    emit ensureOperate("unlock");
}

//�޸�����
void Form::on_btnChange_clicked()
{
    QString passwd=QInputDialog::getText(this,tr("����"),tr("����������:"),QLineEdit::Password);
    if(!passwd.isEmpty())
    {
        if(passwd.count()==6)
        {
                emit ensureOperate("ch"+passwd);
        }
        else
        {
            QMessageBox::warning(this,tr(" "),tr("�������������˶Ժ�����"));
            return;
        }
    }
}

//�������ݵĴ���
void Form::sendDataToEnsureForm(QString what,bool isSuccessful)
{
    if(what==QString("unlock"))
    {
        if(isSuccessful)
        {
            QMessageBox::warning(this,tr(" "),tr("��������ɹ�"));
            return;
        }
        else
        {
            QMessageBox::warning(this,tr(" "),tr("�������ʧ��"));
            return;
        }
    }
    else if(what.mid(0,4)==QString("show"))
    {
        if(isSuccessful)
        {
        QString s="����Ϊ:";
        s.append(what.mid(4,6));
        QMessageBox::warning(this,tr("�鿴����"),s);
        return;
        }
        else
        {
        QMessageBox::warning(this,tr("�鿴����"),tr("��Ƭ����,�������鿴"));
        }
    }
    else if(what==QString("addGuest"))
    {
        if(isSuccessful)
        {
            QMessageBox::information(this,tr("�������"),tr("��������ɹ�"));
            return;
        }
        else
        {
            QMessageBox::information(this,tr("�������"),tr("�������ʧ��"));
            return;
        }
    }
    else if(what==QString("addUser"))
    {
        if(isSuccessful)
        {
            QMessageBox::information(this,tr("����û�"),tr("����û��ɹ�"));
            return;
        }
        else
        {
            QMessageBox::information(this,tr("����û�"),tr("����û�ʧ��"));
            return;
        }
    }
    else if(what==QString("ch"))
    {
        if(isSuccessful)
        {
            QMessageBox::information(this,tr("�޸�����"),tr("�޸�����ɹ�"));
        }
        else
        {
            QMessageBox::information(this,tr("�޸�����"),tr("�޸�����ʧ��"));
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
