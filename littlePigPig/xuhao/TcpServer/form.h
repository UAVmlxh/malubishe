#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void sendDataToEnsureForm(QString what,bool isSuccessful);
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btnShow_clicked();

    void on_btnUnlcok_clicked();

    void on_btnChange_clicked();

    void on_addUser_clicked();

    void on_btnAddGuest_clicked();

    void on_btnExit_clicked();

private:
    Ui::Form *ui;
signals:
    void ensureOperate(QString opt);
    void exitFromEnsureForm();
};

#endif // FORM_H
