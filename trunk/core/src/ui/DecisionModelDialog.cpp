
#include "../../include/ui/DecisionModelDialog.h"
#include "ui_DecisionModelDialog.h"
#include <QDebug>
DecisionModelDialog::DecisionModelDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::DecisionModelDialog) {
    ui->setupUi(this);

    connect(ui->addAlternative, &QPushButton::clicked,this, &DecisionModelDialog::onAddAlternativeButtonClicked);
    connect(ui->addCriteria, &QPushButton::clicked,this, &DecisionModelDialog::onAddCriteriaButtonClicked);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&DecisionModelDialog::onButtonBoxAccepted);
}

DecisionModelDialog::~DecisionModelDialog() {
    delete ui;
}

void DecisionModelDialog::onAddAlternativeButtonClicked()
{
    auto alternativeName = ui->alternativeLineEdit->text();
    if (! alternativeName.isEmpty()){
        ui->alternativesList->addItem(alternativeName);
        ui->alternativeLineEdit->clear();
    }

}

void DecisionModelDialog::onAddCriteriaButtonClicked()
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



const QString &DecisionModelDialog::decisionName() const {
    return decisionName_;
}

void DecisionModelDialog::onButtonBoxAccepted()
{
    for (int i = 0; i < ui->alternativesList->count(); ++i) {
        alternativesNames_.append(ui->alternativesList->item(i)->text());
    }
    for (int i = 0; i < ui->criteriaList->count(); ++i) {
        criteriaNames_.append(ui->criteriaList->item(i)->text());
    }
    decisionName_ = ui->decisionNameLineEdit->text();
    accept();
}

