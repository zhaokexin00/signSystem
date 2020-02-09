#include "widget.h"
#include <QApplication>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogIn l;
    l.show();
//    Widget w;
//    w.show();

    return a.exec();
}
