#include "../../include/ui/StartMenu.h"
#include "ui_StartMenu.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#if 0
static int current_count(){
    static int count = 0;
    return ++count;
}
#endif

StartMenu::StartMenu(QWidget *parent) :
        QWidget(parent), ui(new Ui::StartMenu){
    ui->setupUi(this);
    connect(ui->createModelButton,&QPushButton::clicked,this,&StartMenu::onCreateModelButtonClicked);
    connect(ui->modelsList,&QListWidget::currentRowChanged,this, &StartMenu::onModelListUpdate);
    connect(ui->deleteModelButton,&QPushButton::clicked,this,&StartMenu::onDeleteModelButtonClicked);

    ui->compareAlternativesButton->setEnabled(false);
    ui->compareCriteriaButton->setEnabled(false);

    ui->deleteModelButton->setEnabled(false);
    ui->compareAlternativesButton->setEnabled(ui->alternativesList->count() > 0);
    ui->compareCriteriaButton->setEnabled(ui->criteriaList->count() > 0);
}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::onCreateModelButtonClicked()
{
    auto createModelDialog = new DecisionModelDialog(modelsDb_, this);
    auto res = createModelDialog->exec();
    if (res == QDialog::Accepted){
        qDebug() << "Accepted DecisionModelDialog";
        auto alternativesNames = createModelDialog->alternativesNames();
        auto criteriaNames = createModelDialog->criteriaNames();

        DecisionModel decisionModel;
        for (const auto& alternativeName : alternativesNames) {
            decisionModel.addAlternative(alternativeName.toStdString());
        }
        for (const auto& criterionName : criteriaNames) {
            decisionModel.addCriteria(criterionName.toStdString());
        }
        auto modelName = createModelDialog->decisionName();
        if (! modelName.isEmpty()){
            decisionModel.setDecisionName(modelName.toStdString());
            ui->modelsList->addItem(modelName);

        }
        modelsDb_.addModel(decisionModel.decisionName(), decisionModel);
        auto currentModelIndex = ui->modelsList->count() - 1;
        ui->modelsList->setCurrentRow(currentModelIndex);
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
    }


}


