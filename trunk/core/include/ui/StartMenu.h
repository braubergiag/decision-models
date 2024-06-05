#pragma once

#include <memory>
#include <QWidget>
#include <QPushButton>
#include "DecisionModelDialog.h"
#include "CompareAlternativesDialog.h"
#include "CompareCriteriaDialog.h"
#include "../decision_models_db.h"

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
	void onDecisionModelDialogAccepted(const DecisionModelDialog *createModelDialog,
									   const std::string &oldModelName = {});
	void onModelListUpdate();
	void onEstimateButtonClicked();
	void onModelReady();

private:
	eMode currentState{eMode::eModelNotPrepared};
	DecisionModelsDB modelsDb_;
	Ui::StartMenu *ui;
};
