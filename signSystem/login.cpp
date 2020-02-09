#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include "widget.h"
#include <QSqlQuery>
#include <QDebug>
#include "register.h"


LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon("://01.jpg"));
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("20_sql2");
    db.setUserName("root");
    db.setPassword("123456");

    if(db.open())
    {
        qDebug()<<"success";
    }
    else
    {
        qDebug()<<"false";
    }
    connect(ui->pushButton,QPushButton::clicked,[=](){
        if(ui->lineEdit->text().isEmpty())
        {
            QMessageBox::warning(this,"warning","学号为空");
        }
        else if(ui->lineEdit_2->text().isEmpty())
        {
            QMessageBox::warning(this,"warning","密码为空");
        }
        else
        {
           check(ui->lineEdit->text(),ui->lineEdit_2->text());
        }
    });
}

void LogIn::check(QString sno,QString key)
{
    QSqlQuery q;
    q.exec(QString("select * from student where sno='%1'").arg(sno));

    if(q.size()>0)
    {
        QSqlQuery q1;
        q1.exec(QString("select * from student where sno=%1 and kkey='%2'").arg(sno).arg(key));
        if(q1.size()>0)
        {         
            Widget *w=new Widget(NULL,sno);
            w->show();
            this->close();
        }
        else
        {
           QMessageBox::warning(this,"waining","密码不正确");
        }
    }
    else
    {
       QMessageBox::warning(this,"warning","学号不存在");
    }

}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_pushButton_2_clicked()
{
    Register *r=new Register;
    r->show();
}
