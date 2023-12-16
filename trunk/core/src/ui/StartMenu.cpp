#include "../../include/ui/StartMenu.h"
#include "ui_StartMenu.h"
#include <QVBoxLayout>
#include <QDebug>

StartMenu::StartMenu(QWidget *parent) :
        QWidget(parent), ui(new Ui::StartMenu){
    ui->setupUi(this);
    connect(ui->createModelButton,&QPushButton::clicked,this,&StartMenu::onCreateModelButtonClicked);
    connect(this,&StartMenu::modelListUpdate,this,&StartMenu::onModelListUpdate);

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
        auto alternatives = createModelDialog->alternativesNames();
        auto criteria = createModelDialog->criteriaNames();

        DecisionModel decisionModel;
        for (auto alt : alternatives) {
            decisionModel.addAlternative(alt.toStdString());
        }
        for (auto crit : criteria) {
            decisionModel.addCriteria(crit.toStdString());
        }
        auto modelName = createModelDialog->decisionName();
        if (! modelName.isEmpty()){
            decisionModel.setDecisionName(modelName.toStdString());
            ui->modelsList->addItem(modelName);

        }
        modelsDb_.addModel(decisionModel.decisionName(), decisionModel);
        emit modelListUpdate();

    }


}

void StartMenu::onModelListUpdate() {

    if (modelsDb_.size() > 0) {
        auto currentModelIndex = ui->modelsList->count() - 1;
        ui->modelsList->setCurrentRow(currentModelIndex);

        auto modelName = ui->modelsList->currentItem()->text().toStdString();
        if (modelsDb_.count(modelName)){
            auto model = modelsDb_.model(modelName);

            for (const auto& alt : model.alternativesNames())
                ui->alternativesList->addItem(QString::fromStdString(alt));
            for (const auto& crit : model.criteriaNames())
                ui->criteriaList->addItem(QString::fromStdString(crit));



            ui->compareCriteriaButton->setEnabled(true);
            ui->compareAlternativesButton->setEnabled(true);
        }




    }

}


