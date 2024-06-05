#include <QComboBox>
#include <QDebug>
#include "ui_CompareAlternativesDialog.h"
#include "../../include/ui/CompareAlternativesDialog.h"
#include "../../include/decision_methods/utils.h"

CompareAlternativesDialog::CompareAlternativesDialog(DecisionModel &decisionModel, QWidget *parent)
	: CompareDialogBase(parent), decisionModel_(decisionModel), ui(new Ui::CompareAlternativesDialog) {
	ui->setupUi(this);


	initComboBoxItems();
	initTableWidget();
	initMatrixViews();
	initSignalsAndSlotsConnections();
	updateTableWidget(0);
}

CompareAlternativesDialog::~CompareAlternativesDialog() {
	delete ui;
}

void CompareAlternativesDialog::initSignalsAndSlotsConnections() {
	connect(ui->criteriaComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this,
			&CompareAlternativesDialog::onCriterionChanged);
	connect(ui->criteriaComboBox, qOverload<int>(&QComboBox::activated), this,
			&CompareAlternativesDialog::onCriterionActivated);
	connect(ui->alternativesTableWidget, &QTableWidget::cellChanged, this, &CompareAlternativesDialog::onCellChanged);
	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CompareAlternativesDialog::onButtonBoxAccepted);
	connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &CompareAlternativesDialog::onButtonBoxRejected);
}

void CompareAlternativesDialog::initMatrixViews() {
	matrixValues_.resize(decisionModel_.criteriaCount());
	for (auto &compMatrixValues: matrixValues_)
		compMatrixValues.resize(rowCount_, columnCount_);


	matrixViews_.resize(decisionModel_.criteriaCount());
	for (auto &compMatrixView: matrixViews_)
		compMatrixView.resize(rowCount_, columnCount_);
}

void CompareAlternativesDialog::initComboBoxItems() {

	for (auto &name: decisionModel_.criteriaNames())
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
			auto item = new QTableWidgetItem(kDefaultValueView);
			ui->alternativesTableWidget->setItem(row, column, item);
			ui->alternativesTableWidget->item(row, column)->setData(Qt::WhatsThisRole, kDefaultValue);
		}
	}
}

void CompareAlternativesDialog::onCriterionChanged(int index) {

	saveDataFromTableWidget();
	updateTableWidget(index);

	lastActiveIndex_ = index;
}

void CompareAlternativesDialog::loadTableWidgetAt(int index) {
	if (decisionModel_.compsIsInitAt(index)) {
		for (int row = 0; row < rowCount_; ++row) {
			for (int column = 0; column < columnCount_; ++column) {
				auto value = decisionModel_.compsAt(index)(row, column);
				ui->alternativesTableWidget->item(row, column)->setData(Qt::WhatsThisRole, value);
				auto valueView = decisionModel_.compsViewAt(index)(row, column);
				ui->alternativesTableWidget->item(row, column)->setText(QString::fromStdString(valueView));
			}
		}
	}
}

void CompareAlternativesDialog::setDefaultTableWidgetValues() {

	for (int row = 0; row < rowCount_; ++row) {
		for (int column = 0; column < columnCount_; ++column) {
			ui->alternativesTableWidget->item(row, column)->setData(Qt::WhatsThisRole, kDefaultValue);
			ui->alternativesTableWidget->item(row, column)->setText(kDefaultValueView);
		}
	}
	ui->alternativesTableWidget->update();
}

void CompareAlternativesDialog::onCellChanged(int row, int column) {
	handleCellChanged(ui->alternativesTableWidget, row, column);
}

void CompareAlternativesDialog::updateTableWidget(int index) {
	inUpdateState = true;
	if (decisionModel_.compsIsInitAt(index))
		loadTableWidgetAt(index);
	else
		setDefaultTableWidgetValues();
	inUpdateState = false;
}

void CompareAlternativesDialog::onButtonBoxAccepted() {
	saveDataFromTableWidget();
	accept();
}

void CompareAlternativesDialog::onCriterionActivated(int index) {
	if (decisionModel_.compsIsInitAt(index))
		updateTableWidget(index);
}

void CompareAlternativesDialog::saveDataFromTableWidget() {
	for (int row = 0; row < rowCount_; ++row) {
		for (int col = 0; col < columnCount_; ++col) {
			auto value = ui->alternativesTableWidget->item(row, col)->data(Qt::WhatsThisRole).toString();
			matrixValues_.at(lastActiveIndex_)(row, col) = value.toDouble();

			auto valueView = ui->alternativesTableWidget->item(row, col)->text();
			matrixViews_.at(lastActiveIndex_)(row, col) = valueView.toStdString();
		}
	}
	decisionModel_.setAlternativesCompsAt(matrixValues_.at(lastActiveIndex_), matrixViews_.at(lastActiveIndex_),
										  lastActiveIndex_);
}

void CompareAlternativesDialog::onButtonBoxRejected() {
	reject();
}
