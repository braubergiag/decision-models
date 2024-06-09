#include <QDebug>
#include <QMessageBox>
#include <ui_DecisionModelDialog.h>
#include <DecisionModelDialog.h>

DecisionModelDialog::DecisionModelDialog(QWidget *parent, const DecisionModelsDB &modelsDb)
	: QDialog(parent), modelsDb_(modelsDb), ui(new Ui::DecisionModelDialog) {
	ui->setupUi(this);
	connect(ui->addAlternative, &QPushButton::clicked, this, &DecisionModelDialog::onAddAlternativeButtonClicked);
	connect(ui->addCriteria, &QPushButton::clicked, this, &DecisionModelDialog::onAddCriteriaButtonClicked);
	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DecisionModelDialog::onButtonBoxAccepted);
	connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DecisionModelDialog::onButtonBoxRejected);
	connect(ui->deleteAlternative, &QPushButton::clicked, this, &DecisionModelDialog::onDeleteAlternativeButtonClicked);
	connect(ui->deleteCriteria, &QPushButton::clicked, this, &DecisionModelDialog::onDeleteCriterionButtonClicked);
	editMode_ = false;
}

DecisionModelDialog::DecisionModelDialog(QWidget *parent, const DecisionModelsDB &modelsDb, DecisionModel *model)
	: DecisionModelDialog(parent, modelsDb) {

	decisionModel_ = model;
	ui->modelNameLineEdit->setText(QString::fromStdString(decisionModel_->modelName()));
	setAlternativesListWidget(*decisionModel_);
	setCriteriaListWidget(*decisionModel_);
	editMode_ = true;
}

DecisionModelDialog::~DecisionModelDialog() {
	delete ui;
}

void DecisionModelDialog::onAddAlternativeButtonClicked() {
	auto alternativeName = ui->alternativeLineEdit->text();
	if (alternativeName.isEmpty()) {
		QMessageBox::information(this, "Название альтернативы не задано", "Пожалуйста, укажите название альтернативы");
		return;
	} else if (!ui->alternativesList->findItems(alternativeName, Qt::MatchExactly).isEmpty()) {
		QMessageBox::information(this, "Альтернатива уже указана", "Альтернатива с данным названием уже есть в списке");
		return;
	}
	if (decisionModel_) {
		decisionModel_->addAlternative(alternativeName.toStdString());
	}
	ui->alternativesList->addItem(alternativeName);
	ui->alternativeLineEdit->clear();
}

void DecisionModelDialog::onAddCriteriaButtonClicked() {
	auto criteriaName = ui->criteriaLineEdit->text();
	if (criteriaName.isEmpty()) {
		QMessageBox::information(this, "Название критерия не задано", "Пожалуйста, укажите название критерия");
		return;
	} else if (!ui->criteriaList->findItems(criteriaName, Qt::MatchExactly).isEmpty()) {
		QMessageBox::information(this, "Критерий уже добавлен", "Критерий с данным названием уже есть в списке");
		return;
	}
	if (decisionModel_) {
		decisionModel_->addCriteria(criteriaName.toStdString());
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
		QMessageBox::information(this, "Название модели", "Модель \"" + modelName_ + "\" уже существует.");
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
	if (decisionModel_) {
		auto newModelName = ui->modelNameLineEdit->text().toStdString();
		if (decisionModel_->modelName() != newModelName) {
			if (modelsDb_.count(newModelName)) {
				QMessageBox::information(this, "Название модели",
										 "Модель \"" + QString::fromStdString(newModelName) + "\" уже существует");
				ui->modelNameLineEdit->setText(QString::fromStdString(decisionModel_->modelName()));
				return;
			}
			auto oldName = decisionModel_->modelName();
			decisionModel_->setDecisionName(newModelName);
		}
	}
	accept();
}

void DecisionModelDialog::setAlternativesListWidget(const DecisionModel &model) {
	for (const auto &alternativeName: model.alternativesNames()) {
		ui->alternativesList->addItem(QString::fromStdString(alternativeName));
	}
}

void DecisionModelDialog::setCriteriaListWidget(const DecisionModel &model) {
	for (const auto &criterionName: model.criteriaNames()) {
		ui->criteriaList->addItem(QString::fromStdString(criterionName));
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
	if (decisionModel_) {
		decisionModel_->removeAlternative(alternativeNameRowIndex);
	}
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
	if (decisionModel_) {
		decisionModel_->removeCriteria(criterionNameRowIndex);
	}
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
