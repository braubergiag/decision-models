
#include "../../include/ui/DecisionModelDialog.h"
#include "ui_DecisionModelDialog.h"
#include <QDebug>
#include <QMessageBox>
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
    if (alternativeName.isEmpty()){
        QMessageBox::information(this,"Название не задано","Пожалуйста, укажите название альтернативы");
        return;
    } else if (! ui->alternativesList->findItems(alternativeName,Qt::MatchExactly).isEmpty()){
        QMessageBox::information(this,"Альтернатива уже указана","Альтернатива с данным названием уже есть в списке");
        return;
    }
    ui->alternativesList->addItem(alternativeName);
    ui->alternativeLineEdit->clear();

}

void DecisionModelDialog::onAddCriteriaButtonClicked()
{
    auto criteriaName = ui->criteriaLineEdit->text();
    if (criteriaName.isEmpty()){
        QMessageBox::information(this,"Название не задано","Пожалуйста, укажите название альтернативы");
        return;
    } else if (! ui->alternativesList->findItems(criteriaName,Qt::MatchExactly).isEmpty()){
        QMessageBox::information(this,"Критерий уже добавлен","Критерий с данным названием уже есть в списке");
        return;
    }

    ui->criteriaList->addItem(criteriaName);
    ui->criteriaLineEdit->clear();

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
    decisionName_ = ui->decisionNameLineEdit->text();
    if (decisionName_.isEmpty()){
        QMessageBox::information(this,"Название модели не задано","Пожалуйста, укажите название модели");
        return;
    }
    auto alternativesCount = ui->alternativesList->count();
    if (alternativesCount < kMinAlternativesCount) {
        QMessageBox::information(this,"Альтернатив недостаточно",
                 "Пожалуйста, укажите минимум "+ QString::number(kMinAlternativesCount) +" альтернативы");
        return;
    }
    auto criteriaCount = ui->criteriaList->count();
    if (criteriaCount < kMinCriteriaCount) {
        QMessageBox::information(this,"Критериев недостаточно",
                                 "Пожалуйста, укажите минимум "+ QString::number(kMinCriteriaCount) +" критерий");
        return;
    }

    for (int i = 0; i < alternativesCount; ++i) {
        alternativesNames_.append(ui->alternativesList->item(i)->text());
    }
    for (int i = 0; i < criteriaCount; ++i) {
        criteriaNames_.append(ui->criteriaList->item(i)->text());
    }
    accept();
}

