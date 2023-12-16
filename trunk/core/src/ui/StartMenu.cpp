#include "../../include/ui/StartMenu.h"
#include "ui_StartMenu.h"
#include <QVBoxLayout>
#include <QDebug>

StartMenu::StartMenu(QWidget *parent) :
        QWidget(parent), ui(new Ui::StartMenu){
    ui->setupUi(this);

}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::on_createModelButton_clicked()
{
    auto createModelDialog = new DecisionModelDialog(this);
    auto res = createModelDialog->exec();
    if (res == QDialog::Accepted){
        qDebug() << "Accepted DecisionModelDialog";
    }

    auto alternatives = createModelDialog->alternativesNames();
    auto criteria = createModelDialog->criteriaNames();

    for (auto alt : alternatives) {
        qDebug() << alt << " ";
    }
    qDebug() << "\n";
    for (auto crit : criteria) {
        qDebug() << crit << " ";
    }

}

