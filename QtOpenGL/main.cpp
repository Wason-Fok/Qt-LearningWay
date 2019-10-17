#include <QApplication>
#include "MyGLWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyGLWidget w;
    w.resize(800, 600);
    w.show();

    return app.exec();
}
