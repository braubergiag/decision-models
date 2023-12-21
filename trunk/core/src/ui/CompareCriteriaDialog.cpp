#include "../../include/ui/CompareCriteriaDialog.h"
#include "ui_CompareCriteriaDialog.h"
#include <QVBoxLayout>
#include <QDebug>
#include <iostream>

CompareCriteriaDialog::CompareCriteriaDialog(QWidget *parent, std::vector<std::string> criteriaNames) :
        QDialog(parent), criteriaNames_(criteriaNames), ui(new Ui::CompareCriteriaDialog) {
    ui->setupUi(this);
    rowCount_ = columnCount_ = criteriaNames_.size();
    ui->criteriaTableWidget->setRowCount(rowCount_);
    ui->criteriaTableWidget->setColumnCount(columnCount_);
    static const int kColumnWidth = 20;
    ui->criteriaTableWidget->resize(rowCount_ * 10, columnCount_ * kColumnWidth);

    for (int row = 0; row < rowCount_; ++row) {
        auto headerItem = new QTableWidgetItem(QString::fromStdString(criteriaNames.at(row)));
        ui->criteriaTableWidget->setHorizontalHeaderItem(row, headerItem);
        ui->criteriaTableWidget->setVerticalHeaderItem(row, headerItem);
        for (int column = 0; column < columnCount_; ++column) {
            auto item = new QTableWidgetItem("1");
            ui->criteriaTableWidget->setItem(row, column, item);
            ui->criteriaTableWidget->item(row, column)->setData(Qt::WhatsThisRole, "1.");

        }
    }


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
    for (int row = 0; row < rowCount_; ++row) {
        for (int col = 0; col < columnCount_; ++col) {
            auto value = ui->criteriaTableWidget->item(row,col)->data(Qt::WhatsThisRole).toString();
            double d =  value.toDouble();
            qDebug() << value << " " << d;
            criteriaComparisons_(row,col) = d;
        }
    }
    std::cout << criteriaComparisons_ << "\n";
    accept();

}

const Eigen::MatrixXd &CompareCriteriaDialog::criteriaComparisons() const {
    return criteriaComparisons_;
}
