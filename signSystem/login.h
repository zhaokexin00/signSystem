#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class LogIn;
}

class LogIn : public QWidget
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = 0);
    ~LogIn();
    void check(QString sno,QString key);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::LogIn *ui;
};

#endif // LOGIN_H
