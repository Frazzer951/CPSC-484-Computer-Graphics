#include "mainwindow.h"

#include <QApplication>
//#include "oglwidget.h"
#include "UserInterface/qtraytracer.h"
//#include "Utilities/Matrix.h"

//#include <string.h>
//#include <stdio.h>
//#include <QElapsedTimer>
//#include <unistd.h>



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

//    OglWidget* ogl = new OglWidget();

    RenderCanvas* rc = new RenderCanvas();
    w.setCentralWidget(rc);

    w.show();
    return a.exec();
}
