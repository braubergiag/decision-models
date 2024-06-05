#pragma once
#include <QDialog>
#include <Eigen/Core>
#include "../decision_model.h"
#include "CompareDialogBase.h"
QT_BEGIN_NAMESPACE

namespace Ui {
	class CompareAlternativesDialog;
}

QT_END_NAMESPACE

class CompareAlternativesDialog : public CompareDialogBase {
	Q_OBJECT

public:
	explicit CompareAlternativesDialog(DecisionModel &decisionModel, QWidget *parent = nullptr);

	~CompareAlternativesDialog() override;

public:
public slots:
	void onCriterionChanged(int index);
	void onCriterionActivated(int index);
	void onCellChanged(int row, int column);
	void onButtonBoxAccepted();
	void onButtonBoxRejected();

private:
	void initMatrixViews();
	void initTableWidget();
	void initComboBoxItems();
	void initSignalsAndSlotsConnections();
	void loadTableWidgetAt(int index);
	void setDefaultTableWidgetValues();
	void updateTableWidget(int index);
	void saveDataFromTableWidget();

private:
	DecisionModel &decisionModel_;
	QList<QString> criteriaNames_;
	std::vector<ComparisionMatrixView> matrixViews_;
	std::vector<Eigen::MatrixXd> matrixValues_;
	std::vector<bool> matrixIsInited_;


	int rowCount_;
	int columnCount_;
	int lastActiveIndex_{0};

	const double kDefaultValue{1.};
	const QString kDefaultValueView{"1"};
	bool inUpdateState{false};

private:
	Ui::CompareAlternativesDialog *ui;
};
