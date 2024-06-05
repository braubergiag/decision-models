#pragma once

#include <QDialog>
#include <QTableWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
	class CompareDialogBase;
}
QT_END_NAMESPACE

class CompareDialogBase : public QDialog {
	Q_OBJECT

public:
	explicit CompareDialogBase(QWidget *parent = nullptr);
	~CompareDialogBase() override;
	void handleCellChanged(QTableWidget * tableWidget, int row, int column);

private:
	void handleIntValue(QTableWidget * tableWidget, int row, int column);
	void handleFractionValue(QTableWidget * tableWidget, int row, int column);
	void handleIncorrectValue(QTableWidget * tableWidget, int row, int column);
protected:
	inline static const double kDefaultValue{1.};
	inline static const double kMaxVal = 10;
	inline static const QString kDefaultValueView{"1"};
private:
	Ui::CompareDialogBase *ui;
};

