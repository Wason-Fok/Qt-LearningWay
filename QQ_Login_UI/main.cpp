#include "MyWin.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator myTrans;
    // :/MyWin/MyWin_zh_CN.qm
    myTrans.load(":/MyWin/MyWin_" + QLocale::system().name() + ".qm");
    a.installTranslator(&myTrans);
    MyWin w;
    w.show();

    return a.exec();
}
