#include "../../include/ui/StartMenu.h"
#include "ui_StartMenu.h"
#include <QVBoxLayout>
#include <QDebug>
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
    ui->compareAlternativesButton->setEnabled(false);
    ui->compareCriteriaButton->setEnabled(false);

}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::onCreateModelButtonClicked()
{
    auto createModelDialog = new DecisionModelDialog(this);
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

void StartMenu::onModelListUpdate() {
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
    }

}


