#include "../../include/ui/CompareCriteriaDialog.h"
#include "ui_CompareCriteriaDialog.h"
#include <QVBoxLayout>
#include <QDebug>
#include <iostream>

CompareCriteriaDialog::CompareCriteriaDialog(DecisionModel &decisionModel, QWidget *parent) :
        decisionModel_(decisionModel),
        QDialog(parent),
        ui(new Ui::CompareCriteriaDialog) {
    ui->setupUi(this);

    if (decisionModel_.criteriaComparisonMatrixIsInit())
        loadCriteriaTableWidget();
    else
        initCriteriaTableWidget();


    connect(ui->criteriaTableWidget,&QTableWidget::cellChanged,this, &CompareCriteriaDialog::onCellChanged);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&CompareCriteriaDialog::onButtonBoxAccepted);

}

CompareCriteriaDialog::~CompareCriteriaDialog() {
    delete ui;
}

void CompareCriteriaDialog::onCellChanged(int row, int column) {
    static const double kEpsilon = 0.0001;
    static const double kMaxVal = 10;
    if ( row == column )
    {
        ui->criteriaTableWidget->item( column, row )->setText("1");
        return;
    }
    auto item_value = ui->criteriaTableWidget->item(row, column)->text();
    qDebug() << item_value;
    if (item_value == '1')
        return;

    if (item_value.contains("/")) {
        double symmetric_item_value = ui->criteriaTableWidget->item(column, row)->data(Qt::WhatsThisRole).toDouble();
        if (symmetric_item_value > kEpsilon){
            double inverse_value = 1. / symmetric_item_value;
            ui->criteriaTableWidget->item(row,column)->setData( Qt::WhatsThisRole,QString("%1").arg(inverse_value));
        }

    }
    else {
        double value = item_value.toDouble();
        ui->criteriaTableWidget->item( row, column)->setData( Qt::WhatsThisRole, QString("%1").arg(value));
        if (value > kEpsilon and value <= kMaxVal) {
            ui->criteriaTableWidget->item( column, row )->setText( QString("1/%1").arg( value ));
        }
    }
}

void CompareCriteriaDialog::onButtonBoxAccepted() {
    criteriaComparisons_.resize(rowCount_,columnCount_);
    criteriaMatrixView_.resize(rowCount_,columnCount_);
    for (int row = 0; row < rowCount_; ++row) {
        for (int col = 0; col < columnCount_; ++col) {
            auto value = ui->criteriaTableWidget->item(row,col)->data(Qt::WhatsThisRole).toString();
            auto valueView = ui->criteriaTableWidget->item(row,col)->text();
            criteriaComparisons_(row,col) = value.toDouble();
            criteriaMatrixView_(row,col) = valueView.toStdString();
        }
    }
    decisionModel_.setCriteriaComparisons(criteriaComparisons_,criteriaMatrixView_);
    std::cout << criteriaComparisons_ << "\n";
    std::cout << criteriaMatrixView_ << "\n";
    accept();

}

void CompareCriteriaDialog::initCriteriaTableWidget() {
    rowCount_ = columnCount_ = decisionModel_.criteriaCount();
    ui->criteriaTableWidget->setRowCount(rowCount_);
    ui->criteriaTableWidget->setColumnCount(columnCount_);

    for (int row = 0; row < rowCount_; ++row) {
        auto headerItem = new QTableWidgetItem(QString::fromStdString(decisionModel_.criteriaNames().at(row)));
        ui->criteriaTableWidget->setHorizontalHeaderItem(row, headerItem);
        ui->criteriaTableWidget->setVerticalHeaderItem(row, headerItem);
        for (int column = 0; column < columnCount_; ++column) {
            auto item = new QTableWidgetItem("1");
            ui->criteriaTableWidget->setItem(row, column, item);
            ui->criteriaTableWidget->item(row, column)->setData(Qt::WhatsThisRole, "1.");

        }
    }
}

void CompareCriteriaDialog::loadCriteriaTableWidget() {
    rowCount_ = columnCount_ = decisionModel_.criteriaCount();
    ui->criteriaTableWidget->setRowCount(rowCount_);
    ui->criteriaTableWidget->setColumnCount(columnCount_);

    criteriaComparisons_ = decisionModel_.criteriaComparisons();
    criteriaMatrixView_ = decisionModel_.criteriaComparisonsMatrixView();
    for (int row = 0; row < rowCount_; ++row) {
        auto headerItem = new QTableWidgetItem(QString::fromStdString(decisionModel_.criteriaNames().at(row)));
        ui->criteriaTableWidget->setHorizontalHeaderItem(row, headerItem);
        ui->criteriaTableWidget->setVerticalHeaderItem(row, headerItem);
        for (int column = 0; column < columnCount_; ++column) {
            auto valueView = criteriaMatrixView_(row,column);
            auto item = new QTableWidgetItem(QString::fromStdString(valueView));
            ui->criteriaTableWidget->setItem(row, column, item);

            auto value = criteriaComparisons_(row,column);
            ui->criteriaTableWidget->item(row, column)->setData(Qt::WhatsThisRole, value);

        }
    }

}
