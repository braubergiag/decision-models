
#include "../../include/ui/DecisionModelDialog.h"
#include "ui_DecisionModelDialog.h"
#include <QVBoxLayout>
#include <QGridLayout>

DecisionModelDialog::DecisionModelDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::DecisionModelDialog) {
    ui->setupUi(this);


}

DecisionModelDialog::~DecisionModelDialog() {
    delete ui;
}

void DecisionModelDialog::on_addAlternative_clicked()
{
    auto alternativeName = ui->alternativeLineEdit->text();
    if (! alternativeName.isEmpty()){
        ui->alternativesList->addItem(alternativeName);
        ui->alternativeLineEdit->clear();
    }

}


void DecisionModelDialog::on_addCriteria_clicked()
{
    auto criteriaName = ui->criteriaLineEdit->text();
    if (! criteriaName.isEmpty()){
        ui->criteriaList->addItem(criteriaName);
        ui->criteriaLineEdit->clear();
    }
}


const QVector<QString> &DecisionModelDialog::alternativesNames() const {
    return alternativesNames_;
}

const QVector<QString> &DecisionModelDialog::criteriaNames() const {
    return criteriaNames_;
}





void DecisionModelDialog::on_buttonBox_accepted()
{
    for (int i = 0; i < ui->alternativesList->count(); ++i) {
        alternativesNames_.append(ui->alternativesList->item(i)->text());
    }
    for (int i = 0; i < ui->criteriaList->count(); ++i) {
        criteriaNames_.append(ui->criteriaList->item(i)->text());
    }

    qDebug() << "Accepted";
    accept();
}

