#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/res/icons/stockwatcher.ico"));
    Login w;
    w.show();
    return a.exec();
}
