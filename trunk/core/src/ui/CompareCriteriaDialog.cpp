#include <iostream>
#include <QDebug>
#include "ui_CompareCriteriaDialog.h"
#include "../../include/ui/CompareCriteriaDialog.h"
#include "../../include/decision_methods/utils.h"


CompareCriteriaDialog::CompareCriteriaDialog(DecisionModel &decisionModel, QWidget *parent)
	: decisionModel_(decisionModel), CompareDialogBase(parent), ui(new Ui::CompareCriteriaDialog) {
	ui->setupUi(this);

	if (decisionModel_.criteriaComparisonMatrixIsInit())
		loadCriteriaTableWidget();
	else
		initCriteriaTableWidget();
	connect(ui->criteriaTableWidget, &QTableWidget::cellChanged, this, &CompareCriteriaDialog::onCellChanged);
	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CompareCriteriaDialog::onButtonBoxAccepted);
	connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &CompareCriteriaDialog::onButtonBoxRejected);
}

CompareCriteriaDialog::~CompareCriteriaDialog() {
	delete ui;
}

void CompareCriteriaDialog::onCellChanged(int row, int column) {
	handleCellChanged(ui->criteriaTableWidget, row, column);
}

void CompareCriteriaDialog::onButtonBoxAccepted() {
	criteriaComparisons_.resize(rowCount_, columnCount_);
	criteriaMatrixView_.resize(rowCount_, columnCount_);
	for (int row = 0; row < rowCount_; ++row) {
		for (int col = 0; col < columnCount_; ++col) {
			auto value = ui->criteriaTableWidget->item(row, col)->data(Qt::WhatsThisRole).toString();
			auto valueView = ui->criteriaTableWidget->item(row, col)->text();
			criteriaComparisons_(row, col) = value.toDouble();
			criteriaMatrixView_(row, col) = valueView.toStdString();
		}
	}
	decisionModel_.setCriteriaComparisons(criteriaComparisons_, criteriaMatrixView_);
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
			auto item = new QTableWidgetItem(kDefaultValueView);
			ui->criteriaTableWidget->setItem(row, column, item);
			ui->criteriaTableWidget->item(row, column)->setData(Qt::WhatsThisRole, kDefaultValue);
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
			auto valueView = criteriaMatrixView_(row, column);
			auto item = new QTableWidgetItem(QString::fromStdString(valueView));
			ui->criteriaTableWidget->setItem(row, column, item);

			auto value = criteriaComparisons_(row, column);
			ui->criteriaTableWidget->item(row, column)->setData(Qt::WhatsThisRole, value);
		}
	}
}

void CompareCriteriaDialog::onButtonBoxRejected() {
	reject();
}
