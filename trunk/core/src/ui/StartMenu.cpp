#include "../../include/ui/StartMenu.h"
#include "ui_StartMenu.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QVector>

StartMenu::StartMenu(QWidget *parent) :
        QWidget(parent), ui(new Ui::StartMenu){
    ui->setupUi(this);
    connect(ui->createModelButton,&QPushButton::clicked,this,&StartMenu::onCreateModelButtonClicked);
    connect(ui->modelsList,&QListWidget::currentRowChanged,this, &StartMenu::onModelListUpdate);
    connect(this,&StartMenu::modelUpdated,this, &StartMenu::onModelListUpdate);
    connect(ui->deleteModelButton,&QPushButton::clicked,this,&StartMenu::onDeleteModelButtonClicked);
    connect(ui->editModelButton,&QPushButton::clicked,this,&StartMenu::onEditModelButtonClicked);
    connect(ui->compareAlternativesButton,&QPushButton::clicked,this, &StartMenu::onCompareAlternativesButtonClicked);
    connect(ui->compareCriteriaButton,&QPushButton::clicked,this, &StartMenu::onCompareCriteriaButtonClicked);

    ui->compareAlternativesButton->setEnabled(false);
    ui->compareCriteriaButton->setEnabled(false);
    ui->deleteModelButton->setEnabled(false);
    ui->editModelButton->setEnabled(false);
    ui->compareAlternativesButton->setEnabled(false);
    ui->compareCriteriaButton->setEnabled(false);
}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::onCreateModelButtonClicked()
{
    auto createModelDialog = new DecisionModelDialog(modelsDb_, this);
    auto res = createModelDialog->exec();
    if (res == QDialog::Accepted){
        emit onDecisionModelDialogAccepted(createModelDialog);
    }

}

void StartMenu::onDeleteModelButtonClicked() {
    auto modelNameRowIndex = ui->modelsList->currentRow();
    if (ui->modelsList->count() == 0){
        QMessageBox::information(this,"Модели","В вашем списке пока нет моделей");
        return;
    }
    if (modelNameRowIndex < 0) {
        QMessageBox::information(this,"Модели","Выберите модель для удаления");
        return;
    }
    auto modelName = ui->modelsList->currentItem()->text().toStdString();
    if (modelsDb_.count(modelName)) {
        ui->alternativesList->clear();
        ui->criteriaList->clear();

        auto item = ui->modelsList->takeItem(modelNameRowIndex);
        modelsDb_.deleteModel(modelName);
        delete item;
    }
    ui->compareAlternativesButton->setEnabled(ui->alternativesList->count() > 0);
    ui->compareCriteriaButton->setEnabled(ui->criteriaList->count() > 0);
    ui->deleteModelButton->setEnabled(modelsDb_.size() > 0);
    ui->editModelButton->setEnabled(modelsDb_.size() > 0);


}

void StartMenu::onEditModelButtonClicked() {
    auto modelNameRowIndex = ui->modelsList->currentRow();
    if (ui->modelsList->count() == 0){
        QMessageBox::information(this, "Модели", "В вашем списке пока нет моделей");
        return;
    }
    else if (modelNameRowIndex < 0) {
        QMessageBox::information(this, "Модели", "Выберите модель для редактирования");
        return;
    }
    auto modelName = ui->modelsList->currentItem()->text().toStdString();
    if (modelsDb_.count(modelName)) {
        auto createModelDialog = new DecisionModelDialog(modelsDb_, modelName,this);
        auto res = createModelDialog->exec();
        if (res == QDialog::Accepted){
            emit onDecisionModelDialogAccepted(createModelDialog, modelName);
        }

    }

}

void StartMenu::onModelListUpdate() {
    if (!ui->modelsList->count() > 0 || !ui->modelsList->currentItem())
        return;
    ui->alternativesList->clear();
    ui->criteriaList->clear();

    auto modelName = ui->modelsList->currentItem()->text().toStdString();
    if (modelsDb_.count(modelName)){
        auto model = modelsDb_.model(modelName);

        for (auto& alternativeName : model.alternativesNames())
            ui->alternativesList->addItem(QString::fromStdString(alternativeName));
        for (auto& criterionName : model.criteriaNames())
            ui->criteriaList->addItem(QString::fromStdString(criterionName));

        ui->compareCriteriaButton->setEnabled(true);
        ui->compareAlternativesButton->setEnabled(true);
        ui->deleteModelButton->setEnabled(true);
        ui->editModelButton->setEnabled(true);
    }


}

void StartMenu::onDecisionModelDialogAccepted(const DecisionModelDialog *createModelDialog,
                                              const std::string &oldModelName) {
        qDebug() << "Accepted DecisionModelDialog";
        DecisionModel decisionModel;
        auto modelName = createModelDialog->modelName();
        decisionModel.setDecisionName(modelName.toStdString());

        auto alternativesNames = createModelDialog->alternativesNames();
        auto criteriaNames = createModelDialog->criteriaNames();

        for (const auto& alternativeName : alternativesNames) {
            decisionModel.addAlternative(alternativeName.toStdString());
        }
        for (const auto& criterionName : criteriaNames) {
            decisionModel.addCriteria(criterionName.toStdString());
        }
         modelsDb_.addOrUpdateModel(decisionModel.decisionName(), decisionModel);

        if (!oldModelName.empty() && oldModelName != modelName.toStdString()){
            modelsDb_.deleteModel(oldModelName);

            auto modelNameIndex = ui->modelsList->currentRow();
            auto item = ui->modelsList->takeItem(modelNameIndex);
            delete item;
            ui->modelsList->insertItem(modelNameIndex,modelName);
            emit modelUpdated();
        } else {
            ui->modelsList->addItem(modelName);
            auto currentModelIndex = ui->modelsList->count() - 1;
            ui->modelsList->setCurrentRow(currentModelIndex);

        }
}

void StartMenu::onCompareAlternativesButtonClicked() {
    auto modelName = ui->modelsList->currentItem()->text().toStdString();

    if (ui->alternativesList->count() > 0) {
        auto compareAlternativesDialog = new CompareAlternativesDialog(this);
        compareAlternativesDialog->exec();
    }

}

void StartMenu::onCompareCriteriaButtonClicked() {
    auto modelName = ui->modelsList->currentItem()->text().toStdString();

    if (ui->criteriaList->count() > 0){

        auto compareCriteriaDialog = new CompareCriteriaDialog(this,modelsDb_.model(modelName).criteriaNames());
        compareCriteriaDialog->exec();
    }
}

