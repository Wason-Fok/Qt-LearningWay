#include "Sender.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sender w;
    w.show();
    return a.exec();
}