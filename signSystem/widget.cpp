#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QCheckBox>
#include <QDateTime>
#include <QMessageBox>
#include "person.h"
#include "login.h"

Widget::Widget(QWidget *parent,QString ssno) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->setWindowIcon(QIcon("://01.jpg"));

    this->ssno=ssno;
    ui->setupUi(this);

    dataToTable("select * from student");
    displayClass();
    displaySno();


    connect(ui->tableWidget,QTableWidget::cellDoubleClicked,[=](int r,int c){
        Person *p=new Person;//new一个空间
        p->displayData(ui->tableWidget->item(r,0)->text(),ui->tableWidget->item(r,1)->text());
        p->show();
    });

}
void Widget::dataToTable(QString sql)
{

    QSqlQuery q;//开始在表的最上面

    if(q.exec(sql))
    {
        ui->tableWidget->setRowCount(q.size());//q.siae()返回行数
        int i=0;//行
        while(q.next())
        {
           QCheckBox *c=new QCheckBox("未签到");
           QString sno=q.value(0).toString();

           //显示已经签到过的
           QSqlQuery q3;
           q3.exec(QString("select stime from ssign "
                           "where sno=%1 and date(stime)=curdate() "
                           "order by stime desc").arg(sno));
           q3.next();

           if(sno!=ssno)
           {
               c->setDisabled(true);
           }

           if(q3.size())
           {
               c->setText("已签到");
               c->setDisabled(true);
               c->setChecked(true);
               ui->tableWidget->setItem(i,4,new QTableWidgetItem(q3.value(0).toString()));
           }

           ui->tableWidget->setItem(i,0,new QTableWidgetItem(sno));
           ui->tableWidget->setItem(i,1,new QTableWidgetItem(q.value(1).toString()));
           ui->tableWidget->setItem(i,2,new QTableWidgetItem(q.value(2).toString()));
           ui->tableWidget->setCellWidget(i,3,c);

           connect(c,QCheckBox::clicked,[=](){
               //1.修改控件本身的状态
               c->setText("已签到");
               c->setDisabled(true);
               //2.向表格中添加本人签到时间
               ui->tableWidget->setItem(i,4,new QTableWidgetItem(QDateTime::currentDateTime().toString()));
               //3.向数据库中插入一条数据
               QSqlQuery q1;
               qDebug()<<q1.exec(QString("insert into ssign values(%1,now())").arg(sno));//QString里的arg函数可以作为占位符使用
           });
           i++;
        };
    }
}

void Widget::displayClass()
{
    QSqlQuery q4;
    q4.exec("select distinct class from student");
    ui->comboBox->addItem("全部班级");
    while(q4.next())
    {
        ui->comboBox->addItem(q4.value(0).toString());
    }

    connect(ui->comboBox,QComboBox::currentTextChanged,[=](QString text){
        if(text=="全部班级")
        {
            dataToTable("select * from student");
        }
        else
        {
            dataToTable(QString("select * from student where class='%1'").arg(text));
        }
    });
}

void Widget::displaySno()
{
    connect(ui->pushButton,QPushButton::clicked,[=](){
        if(ui->lineEdit->text().isEmpty())
        {
            QMessageBox::warning(this,"warn","输入为空");
        }
        else
        {
            dataToTable(QString("select * from student where sno like'%1'").arg(ui->lineEdit->text()));
        }
    });
}

Widget::~Widget()
{
    delete ui;
}
