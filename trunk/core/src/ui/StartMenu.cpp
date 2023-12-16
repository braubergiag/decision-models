#include "../../include/ui/StartMenu.h"
#include "ui_StartMenu.h"
#include <QVBoxLayout>
#include <QDebug>

StartMenu::StartMenu(QWidget *parent) :
        QWidget(parent), ui(new Ui::StartMenu){
    ui->setupUi(this);
    connect(ui->createModelButton,&QPushButton::clicked,this,&StartMenu::onCreateModelButtonClicked);

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

    }

}

