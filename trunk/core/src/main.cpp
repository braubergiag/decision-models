
#include <QApplication>

#include "../include/ui/start_menu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    start_menu startMenu;
    startMenu.show();

    return a.exec();
}
