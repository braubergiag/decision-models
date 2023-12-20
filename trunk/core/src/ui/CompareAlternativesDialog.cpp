
#include "../../include/ui/CompareAlternativesDialog.h"
#include "ui_CompareAlternativesDialog.h"


CompareAlternativesDialog::CompareAlternativesDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::CompareAlternativesDialog) {
    ui->setupUi(this);
}

CompareAlternativesDialog::~CompareAlternativesDialog() {
    delete ui;
}
