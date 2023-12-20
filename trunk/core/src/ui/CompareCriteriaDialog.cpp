#include "../../include/ui/CompareCriteriaDialog.h"
#include "ui_CompareCriteriaDialog.h"


CompareCriteriaDialog::CompareCriteriaDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::CompareCriteriaDialog) {
    ui->setupUi(this);
}

CompareCriteriaDialog::~CompareCriteriaDialog() {
    delete ui;
}
