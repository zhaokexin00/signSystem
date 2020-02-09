#include "register.h"
#include "ui_register.h"
#include "QDebug"
#include "QSqlQuery"
#include "QMessageBox"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("://01.jpg"));
}

Register::~Register()
{
    delete ui;
}


void Register::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec(QString("select sno from student where sno='%1'").arg(ui->lineEdit->text()));
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"warning","学号为空");
    }
    else
    {
        if(ui->lineEdit_2->text().isEmpty())
        {
            QMessageBox::warning(this,"warning","密码为空");
        }
        else
        {
            if(q.size())
            {
                QMessageBox::warning(this,"warning","学号已存在");
            }
            else
            {
                QSqlQuery q1;
                q1.exec(QString("insert into student values('%1','%2','%3','%4')").arg(ui->lineEdit->text())
                                                                                  .arg(ui->lineEdit_3->text())
                                                                                  .arg(ui->lineEdit_4->text())
                                                                                  .arg(ui->lineEdit_2->text()));
                QMessageBox::warning(this," ","注册成功");
            }
        }
    }
}
