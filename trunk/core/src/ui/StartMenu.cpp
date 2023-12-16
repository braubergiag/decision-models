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
        dmodel_ptr_ = std::make_shared<DecisionModel>();
        auto alternatives = createModelDialog->alternativesNames();
        auto criteria = createModelDialog->criteriaNames();


        for (auto alt : alternatives) {
            dmodel_ptr_->addAlternative(alt.toStdString());
        }
        for (auto crit : criteria) {
            dmodel_ptr_->addCriteria(crit.toStdString());
        }
        dmodel_ptr_->set_decision_name(createModelDialog->decisionName().toStdString());
    }

}

