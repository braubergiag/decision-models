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
    auto modelNameIndex = ui->modelsList->currentRow();
    if (modelNameIndex < 0) {
        QMessageBox::information(this,"Модели","В вашем списке пока нет моделей");
        return;
    }
    auto modelName = ui->modelsList->currentItem()->text().toStdString();
    if (modelsDb_.count(modelName)) {
        ui->alternativesList->clear();
        ui->criteriaList->clear();

        auto item = ui->modelsList->takeItem(modelNameIndex);
        modelsDb_.deleteModel(modelName);
        delete item;
    }
    ui->compareAlternativesButton->setEnabled(ui->alternativesList->count() > 0);
    ui->compareCriteriaButton->setEnabled(ui->criteriaList->count() > 0);
    ui->deleteModelButton->setEnabled(modelsDb_.size() > 0);
    ui->editModelButton->setEnabled(modelsDb_.size() > 0);


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

void StartMenu::onEditModelButtonClicked() {
    auto modelNameIndex = ui->modelsList->currentRow();
    if (modelNameIndex < 0) {
        QMessageBox::information(this, "Модели", "В вашем списке пока нет моделей");
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
#if 0
        if (modelName.toStdString() != oldModelName){
            modelsDb_.deleteModel(oldModelName);

            auto modelNameIndex = ui->modelsList->currentRow();
            auto item = ui->modelsList->takeItem(modelNameIndex);
            delete item;
            ui->modelsList->insertItem(modelNameIndex,modelName);

        }
#endif
        if (oldModelName.empty())
                ui->modelsList->addItem(modelName);
        modelsDb_.addOrUpdateModel(decisionModel.decisionName(), decisionModel);
        auto currentModelIndex = ui->modelsList->count() - 1;
        ui->modelsList->setCurrentRow(currentModelIndex);
        emit modelUpdated();
}

