#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QVector>
#include <QString>
#include "../decision_models_db.h"

QT_BEGIN_NAMESPACE

namespace Ui {
	class DecisionModelDialog;
}

QT_END_NAMESPACE

class DecisionModelDialog : public QDialog {
	Q_OBJECT

public:
	explicit DecisionModelDialog(const DecisionModelsDB &modelsDb, QWidget *parent = nullptr);
	DecisionModelDialog(const DecisionModelsDB &modelsDb, const std::string &modelName, QWidget *parent = nullptr);
	~DecisionModelDialog() override;
private slots:
	void onAddAlternativeButtonClicked();
	void onAddCriteriaButtonClicked();
	void onDeleteAlternativeButtonClicked();
	void onDeleteCriterionButtonClicked();

	void onButtonBoxAccepted();
	void onButtonBoxRejected();

public:
	const QString &modelName() const;
	const QVector<QString> &alternativesNames() const;
	const QVector<QString> &criteriaNames() const;

private:
	void initSignalAndSlots();
	void setAlternativesListWidget(const DecisionModelsDB &modelsDb);
	void setCriteriaListWidget(const DecisionModelsDB &modelsDb);

private:
	const int kMinAlternativesCount{2};
	const int kMinCriteriaCount{1};

	const DecisionModelsDB &modelsDb_;

	QString modelName_;
	QVector<QString> alternativesNames_;
	QVector<QString> criteriaNames_;
	bool editMode_{false};
	bool isInit_{false};


	Ui::DecisionModelDialog *ui;
};
