#include "person.h"
#include "ui_person.h"
#include "qsqlquery.h"
#include "QTextCharFormat"

Person::Person(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("://01.jpg"));
}

void Person::displayData(QString sno,QString sname)
{
    ui->label->setText("学号 ："+sno);
    ui->label_2->setText("姓名："+sname);

    QSqlQuery q;
    q.exec(QString("select stime from ssign "
                   "where sno=%1 and date_format(stime,'%Y-%m')"
                   "=date_format(curdate(),'%Y-%m')").arg(sno));
    ui->label_3->setText("本月签到次数： "+QString::number(q.size()));

    QSqlQuery q1;
    q1.exec(QString("select stime from ssign where sno='%1' and year(stime)=year(curdate())").arg(sno));

    QTextCharFormat t;
    t.setBackground(Qt::gray);
    while(q.next())
    {
        ui->calendarWidget->setDateTextFormat(q1.value(0).toDate(),t);
    }


}

Person::~Person()
{
    delete ui;
}
