#include "mainwindow.h"

#include <QApplication>
#include "core/include/tropical_decision_method.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();
    return a.exec();
}
