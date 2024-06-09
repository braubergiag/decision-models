#pragma once

#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <DecisionModelDialog.h>
#include <CompareAlternativesDialog.h>
#include <CompareCriteriaDialog.h>
#include <decision_models_db.h>

QT_BEGIN_NAMESPACE

namespace Ui {
	class StartMenu;
}

QT_END_NAMESPACE

class StartMenu : public QWidget {
	Q_OBJECT
private:
	enum class eMode {
		eModelNotPrepared,
		eModelPrepared
	};


public:
	explicit StartMenu(QWidget *parent = nullptr);

	~StartMenu() override;
signals:
	void decisionModelDialogAccepted();
	void modelUpdated();
	void modelReady();

private:
	void switchState(eMode newState);

private slots:
	void onCreateModelButtonClicked();
	void onDeleteModelButtonClicked();
	void onEditModelButtonClicked();
	void onCompareAlternativesButtonClicked();
	void onCompareCriteriaButtonClicked();
	void onDecisionModelDialogAccepted(const DecisionModelDialog *createModelDialog);
	void onEditDecisionModelDialogAccepted(const DecisionModelDialog *createModelDialog, DecisionModel *model,
										   DecisionModelsDB &db);
	void onModelListUpdate();
	void onEstimateButtonClicked();
	void onMethodChoose();
	void onModelReady();
	void clearModelResults(const QString &modelName);

private:
	eMode currentState{eMode::eModelNotPrepared};
	QString lastActiveModel_;
	DecisionModelsDB modelsDb_;
	Ui::StartMenu *ui;
};
