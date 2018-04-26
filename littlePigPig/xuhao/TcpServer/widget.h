#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
//得到本机网络信息的头文件
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QNetworkInterface>
#include <QList>
#include <QtNetwork/QHostAddress>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QPaintEvent>
#include <QPainter>
#include "form.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void newConnectionSlot();
    void readyReadSlot();
    void on_btnUser_clicked();

    void on_btnGuest_clicked();
    void on_btnEnsure_clicked();
    void ensureOperateSlot(QString opt);
    void exitFromEnsureFormSlot();

protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    QTcpServer *tcpServer; //服务器类
    QTcpSocket *tcpClient; //客户端类
    QString myAddress; //服务器的ip地址和端口
    Form myEnsure;
    int myPort;
};

#endif // WIDGET_H
