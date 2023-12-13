#include "../../include/ui/start_menu.h"
#include "ui_start_menu.h"


start_menu::start_menu(QWidget *parent) :
        QWidget(parent), ui(new Ui::start_menu) {
    ui->setupUi(this);
}

start_menu::~start_menu() {
    delete ui;
}
