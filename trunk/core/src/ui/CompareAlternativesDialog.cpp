
#include "../../include/ui/CompareAlternativesDialog.h"
#include "ui_CompareAlternativesDialog.h"
#include <QComboBox>
#include <QDebug>

CompareAlternativesDialog::CompareAlternativesDialog(DecisionModel &decisionModel, QWidget *parent) :
        QDialog(parent),
        decisionModel_(decisionModel),
        ui(new Ui::CompareAlternativesDialog) {
    ui->setupUi(this);


    initComboBoxItems();
    initTableWidget();
    initMatrixViews();

    connect(ui->criteriaComboBox,qOverload<int>(&QComboBox::currentIndexChanged),this,&CompareAlternativesDialog::onCriteriaChanged);
    connect(ui->alternativesTableWidget,&QTableWidget::cellChanged,this,&CompareAlternativesDialog::onCellChanged);

}

void CompareAlternativesDialog::initMatrixViews() {
    matrixValues_.resize(decisionModel_.criteriaCount());
    for (auto & compMatrixValues : matrixValues_)
        compMatrixValues.resize(rowCount_, columnCount_);


    matrixViews_.resize(decisionModel_.criteriaCount());
    for (auto & compMatrixView : matrixViews_)
        compMatrixView.resize(rowCount_,columnCount_);
}



void CompareAlternativesDialog::initComboBoxItems() {

    for (auto & name: decisionModel_.criteriaNames())
        criteriaNames_.append(QString::fromStdString(name));
    ui->criteriaComboBox->addItems(criteriaNames_);

}

void CompareAlternativesDialog::initTableWidget() {
    rowCount_ = columnCount_ = decisionModel_.alternativesCount();
    ui->alternativesTableWidget->setRowCount(rowCount_);
    ui->alternativesTableWidget->setColumnCount(columnCount_);

    for (int row = 0; row < rowCount_; ++row) {
        auto headerItem = new QTableWidgetItem(QString::fromStdString(decisionModel_.alternativesNames().at(row)));
        ui->alternativesTableWidget->setHorizontalHeaderItem(row, headerItem);
        ui->alternativesTableWidget->setVerticalHeaderItem(row, headerItem);
        for (int column = 0; column < columnCount_; ++column) {
            auto item = new QTableWidgetItem("1");
            ui->alternativesTableWidget->setItem(row, column, item);
            ui->alternativesTableWidget->item(row, column)->setData(Qt::WhatsThisRole, "1.");

        }
    }
}

CompareAlternativesDialog::~CompareAlternativesDialog() {
    delete ui;
}

void CompareAlternativesDialog::onCriteriaChanged(int index) {

    qDebug() << "last active index " << lastActiveIndex_;
    qDebug() << "On criteria Changed() current index:; " << index;
    for (int row = 0; row < rowCount_; ++row) {
        for (int col = 0; col < columnCount_; ++col) {
            auto value = ui->alternativesTableWidget->item(row,col)->data(Qt::WhatsThisRole).toString();
            matrixValues_.at(lastActiveIndex_)(row,col) = value.toDouble();

            auto valueView = ui->alternativesTableWidget->item(row,col)->text();
            matrixViews_.at(lastActiveIndex_)(row,col) = valueView.toStdString();

        }
    }
    decisionModel_.setAlternativesCompsAt(matrixValues_.at(lastActiveIndex_),
                                          matrixViews_.at(lastActiveIndex_),
                                          lastActiveIndex_);
    std::cout << matrixViews_.at(lastActiveIndex_) << "\n";
    std::cout << matrixValues_.at(lastActiveIndex_) << "\n";
    lastActiveIndex_ = index;
}

void CompareAlternativesDialog::onCellChanged(int row, int column) {
        static const double kEpsilon = 0.0001;
        static const double kMaxVal = 10;
        if ( row == column )
        {
            ui->alternativesTableWidget->item( column, row )->setText("1");
            return;
        }
        auto item_value = ui->alternativesTableWidget->item(row, column)->text();
        qDebug() << item_value;
        if (item_value == '1')
            return;

        if (item_value.contains("/")) {
            double symmetric_item_value = ui->alternativesTableWidget->item(column, row)->data(Qt::WhatsThisRole).toDouble();
            if (symmetric_item_value > kEpsilon){
                double inverse_value = 1. / symmetric_item_value;
                ui->alternativesTableWidget->item(row,column)->setData( Qt::WhatsThisRole,QString("%1").arg(inverse_value));
            }

        }
        else {
            double value = item_value.toDouble();
            ui->alternativesTableWidget->item( row, column)->setData( Qt::WhatsThisRole, QString("%1").arg(value));
            if (value > kEpsilon and value <= kMaxVal) {
                ui->alternativesTableWidget->item( column, row )->setText( QString("1/%1").arg( value ));
            }
        }
}
