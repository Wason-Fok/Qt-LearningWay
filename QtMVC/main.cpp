#include "QtMVC.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtMVC w;
    w.show();
    return a.exec();
}
