#include "ui_DecisionModelDialog.h"
#include <QDebug>
#include <QMessageBox>
#include "../../include/ui/DecisionModelDialog.h"

DecisionModelDialog::DecisionModelDialog(const DecisionModelsDB &modelsDb, QWidget *parent)
	: QDialog(parent), modelsDb_(modelsDb), ui(new Ui::DecisionModelDialog) {
	ui->setupUi(this);

	initSignalAndSlots();
	editMode_ = false;
}

DecisionModelDialog::DecisionModelDialog(const DecisionModelsDB &modelsDb, const string &modelName, QWidget *parent)
	: QDialog(parent), modelsDb_(modelsDb), modelName_(QString::fromStdString(modelName)),
	  ui(new Ui::DecisionModelDialog) {

	ui->setupUi(this);

	initSignalAndSlots();
	ui->modelNameLineEdit->setText(modelName_);
	setAlternativesListWidget(modelsDb_);
	setCriteriaListWidget(modelsDb_);
	editMode_ = true;
}

void DecisionModelDialog::initSignalAndSlots() {

	connect(ui->addAlternative, &QPushButton::clicked, this, &DecisionModelDialog::onAddAlternativeButtonClicked);
	connect(ui->addCriteria, &QPushButton::clicked, this, &DecisionModelDialog::onAddCriteriaButtonClicked);
	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DecisionModelDialog::onButtonBoxAccepted);
	connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DecisionModelDialog::onButtonBoxRejected);
	connect(ui->deleteAlternative, &QPushButton::clicked, this, &DecisionModelDialog::onDeleteAlternativeButtonClicked);
	connect(ui->deleteCriteria, &QPushButton::clicked, this, &DecisionModelDialog::onDeleteCriterionButtonClicked);
}

DecisionModelDialog::~DecisionModelDialog() {
	delete ui;
}
void DecisionModelDialog::onAddAlternativeButtonClicked() {
	auto alternativeName = ui->alternativeLineEdit->text();
	if (alternativeName.isEmpty()) {
		QMessageBox::information(this, "Название не задано", "Пожалуйста, укажите название альтернативы");
		return;
	} else if (!ui->alternativesList->findItems(alternativeName, Qt::MatchExactly).isEmpty()) {
		QMessageBox::information(this, "Альтернатива уже указана", "Альтернатива с данным названием уже есть в списке");
		return;
	}
	ui->alternativesList->addItem(alternativeName);
	ui->alternativeLineEdit->clear();
}

void DecisionModelDialog::onAddCriteriaButtonClicked() {
	auto criteriaName = ui->criteriaLineEdit->text();
	if (criteriaName.isEmpty()) {
		QMessageBox::information(this, "Название не задано", "Пожалуйста, укажите название альтернативы");
		return;
	} else if (!ui->criteriaList->findItems(criteriaName, Qt::MatchExactly).isEmpty()) {
		QMessageBox::information(this, "Критерий уже добавлен", "Критерий с данным названием уже есть в списке");
		return;
	}

	ui->criteriaList->addItem(criteriaName);
	ui->criteriaLineEdit->clear();
}

void DecisionModelDialog::onButtonBoxAccepted() {
	modelName_ = ui->modelNameLineEdit->text();
	if (modelName_.isEmpty()) {
		QMessageBox::information(this, "Название модели", "Пожалуйста, укажите название модели");
		return;
	} else if (!editMode_ && modelsDb_.count(modelName_.toStdString()) > 0) {
		QMessageBox::information(this, "Название модели", "Модель с данным названием уже существует");
		return;
	}

	auto alternativesCount = ui->alternativesList->count();
	if (alternativesCount < kMinAlternativesCount) {
		QMessageBox::information(this, "Альтернатив недостаточно",
								 "Пожалуйста, укажите минимум " + QString::number(kMinAlternativesCount) +
										 " альтернативы");
		return;
	}
	auto criteriaCount = ui->criteriaList->count();
	if (criteriaCount < kMinCriteriaCount) {
		QMessageBox::information(this, "Критериев недостаточно",
								 "Пожалуйста, укажите минимум " + QString::number(kMinCriteriaCount) + " критерий");
		return;
	}

	for (int i = 0; i < alternativesCount; ++i) {
		alternativesNames_.append(ui->alternativesList->item(i)->text());
	}
	for (int i = 0; i < criteriaCount; ++i) {
		criteriaNames_.append(ui->criteriaList->item(i)->text());
	}
	accept();
}


void DecisionModelDialog::setAlternativesListWidget(const DecisionModelsDB &modelsDb) {
	auto modelNameStd = modelName_.toStdString();
	if (modelsDb.count(modelNameStd)) {
		auto &model = modelsDb_.model(modelNameStd);
		for (const auto &alternativeName: model.alternativesNames()) {
			ui->alternativesList->addItem(QString::fromStdString(alternativeName));
		}
	}
}

void DecisionModelDialog::setCriteriaListWidget(const DecisionModelsDB &modelsDb) {
	auto modelNameStd = modelName_.toStdString();
	if (modelsDb.count(modelNameStd)) {
		auto &model = modelsDb_.model(modelNameStd);
		for (const auto &criterionName: model.criteriaNames()) {
			ui->criteriaList->addItem(QString::fromStdString(criterionName));
		}
	}
}

void DecisionModelDialog::onDeleteAlternativeButtonClicked() {
	auto alternativeNameRowIndex = ui->alternativesList->currentRow();
	if (ui->alternativesList->count() == 0) {
		QMessageBox::information(this, "Альтернативы", "В вашем списке нет альтернатив");
		return;
	} else if (alternativeNameRowIndex < 0) {
		QMessageBox::information(this, "Альтернативы", "Выберите альтернативу для удаления");
		return;
	}
	auto item = ui->alternativesList->takeItem(alternativeNameRowIndex);
	delete item;
}

void DecisionModelDialog::onDeleteCriterionButtonClicked() {
	auto criterionNameRowIndex = ui->criteriaList->currentRow();
	if (ui->criteriaList->count() == 0) {
		QMessageBox::information(this, "Критерии", "В вашем списке нет критериев");
		return;
	} else if (criterionNameRowIndex < 0) {
		QMessageBox::information(this, "Критерии", "Выберите критерий для удаления");
		return;
	}
	auto item = ui->criteriaList->takeItem(criterionNameRowIndex);
	delete item;
}

void DecisionModelDialog::onButtonBoxRejected() {
	reject();
}


const QVector<QString> &DecisionModelDialog::alternativesNames() const {
	return alternativesNames_;
}

const QVector<QString> &DecisionModelDialog::criteriaNames() const {
	return criteriaNames_;
}

const QString &DecisionModelDialog::modelName() const {
	return modelName_;
}
