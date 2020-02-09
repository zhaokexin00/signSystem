#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0,QString ssno=NULL);
    ~Widget();
    QString ssno;
    void dataToTable(QString sql);
    void displayClass();
    void displaySno();




private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
