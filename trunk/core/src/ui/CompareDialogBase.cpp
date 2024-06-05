#include <sstream>
#include <CompareDialogBase.h>
#include <ui_CompareDialogBase.h>
#include <utils.h>

CompareDialogBase::CompareDialogBase(QWidget *parent) : QDialog(parent), ui(new Ui::CompareDialogBase) {
	ui->setupUi(this);
}

CompareDialogBase::~CompareDialogBase() {
	delete ui;
}

bool CompareDialogBase::isFraction(const QString &input) const {
	return input.contains("/");
}

bool CompareDialogBase::isInteger(const QString &input) const {
	bool ok;
	input.toInt(&ok);
	return ok;
}

bool CompareDialogBase::isDefaultValue(const QString &input) const {
	return input == kDefaultValueView;
}

void CompareDialogBase::handleCellChanged(QTableWidget *tableWidget, int row, int column) {
	if (row == column) {
		tableWidget->item(column, row)->setText(kDefaultValueView);
		return;
	}

	auto item_value = tableWidget->item(row, column)->text();
	if (isFraction(item_value)) {
		handleFractionValue(tableWidget, row, column);
	} else if (isInteger(item_value)) {
		handleIntValue(tableWidget, row, column);
	} else {
		handleIncorrectValue(tableWidget, row, column);
	}
}

void CompareDialogBase::handleIntValue(QTableWidget *tableWidget, int row, int column) {
	auto item_value = tableWidget->item(row, column)->text();
	auto value = abs(item_value.toInt());
	if (value > kMinVal && value <= kMaxVal) {
		tableWidget->item(row, column)->setData(Qt::WhatsThisRole, QString("%1").arg(value));
		tableWidget->item(column, row)->setText(QString::fromStdString(utils::Fraction(1, value).view()));
	} else {
		handleIncorrectValue(tableWidget, row, column);
	}
}

void CompareDialogBase::handleFractionValue(QTableWidget *tableWidget, int row, int column) {
	using namespace utils;
	utils::Fraction frac;
	std::istringstream is(tableWidget->item(row, column)->text().toStdString());
	is >> frac;
	auto item_value = frac.value();
	if (item_value > kMinVal && less_or_equal_than(item_value, kMaxVal)) {
		tableWidget->item(row, column)->setData(Qt::WhatsThisRole, frac.value());
		tableWidget->item(column, row)->setText(QString::fromStdString(frac.inv_view()));
		tableWidget->item(column, row)->setData(Qt::WhatsThisRole, frac.inv_value());
	} else {
		handleIncorrectValue(tableWidget, row, column);
	}
}

void CompareDialogBase::handleIncorrectValue(QTableWidget *tableWidget, int row, int column) {
	tableWidget->item(row, column)->setText(kDefaultValueView);
	tableWidget->item(row, column)->setData(Qt::WhatsThisRole, kDefaultValue);
	tableWidget->item(column, row)->setData(Qt::WhatsThisRole, kDefaultValue);
	tableWidget->item(column, row)->setData(Qt::WhatsThisRole, kDefaultValueView);
}
