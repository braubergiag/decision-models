#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <ui_StartMenu.h>
#include <StartMenu.h>

StartMenu::StartMenu(QWidget *parent) : QWidget(parent), ui(new Ui::StartMenu) {
	ui->setupUi(this);
	connect(ui->createModelButton, &QPushButton::clicked, this, &StartMenu::onCreateModelButtonClicked);
	connect(ui->modelsList, &QListWidget::currentRowChanged, this, &StartMenu::onModelListUpdate);
	connect(this, &StartMenu::modelUpdated, this, &StartMenu::onModelListUpdate);
	connect(ui->deleteModelButton, &QPushButton::clicked, this, &StartMenu::onDeleteModelButtonClicked);
	connect(ui->editModelButton, &QPushButton::clicked, this, &StartMenu::onEditModelButtonClicked);
	connect(ui->compareAlternativesButton, &QPushButton::clicked, this, &StartMenu::onCompareAlternativesButtonClicked);
	connect(ui->compareCriteriaButton, &QPushButton::clicked, this, &StartMenu::onCompareCriteriaButtonClicked);
	connect(ui->estimateButton, &QPushButton::clicked, this, &StartMenu::onEstimateButtonClicked);
	connect(this, &StartMenu::modelReady, this, &StartMenu::onModelReady);

	ui->compareAlternativesButton->setEnabled(false);
	ui->compareCriteriaButton->setEnabled(false);
	ui->deleteModelButton->setEnabled(false);
	ui->editModelButton->setEnabled(false);
	ui->compareAlternativesButton->setEnabled(false);
	ui->compareCriteriaButton->setEnabled(false);

	switchState(eMode::eModelNotPrepared);
}

StartMenu::~StartMenu() {
	delete ui;
}

void StartMenu::onCreateModelButtonClicked() {
	auto createModelDialog = new DecisionModelDialog(this, modelsDb_);
	auto res = createModelDialog->exec();
	if (res == QDialog::Accepted) {
		emit onDecisionModelDialogAccepted(createModelDialog);
		switchState(eMode::eModelNotPrepared);
	}
}

void StartMenu::onDeleteModelButtonClicked() {
	auto modelNameRowIndex = ui->modelsList->currentRow();
	if (ui->modelsList->count() == 0) {
		QMessageBox::information(this, "Модели", "В вашем списке пока нет моделей");
		return;
	}
	if (modelNameRowIndex < 0) {
		QMessageBox::information(this, "Модели", "Выберите модель для удаления");
		return;
	}
	auto modelName = ui->modelsList->currentItem()->text().toStdString();
	if (modelsDb_.count(modelName)) {
		ui->alternativesList->clear();
		ui->criteriaList->clear();

		auto item = ui->modelsList->takeItem(modelNameRowIndex);
		modelsDb_.deleteModel(modelName);
		delete item;
	}
	ui->compareAlternativesButton->setEnabled(ui->alternativesList->count() > 0);
	ui->compareCriteriaButton->setEnabled(ui->criteriaList->count() > 0);
	ui->deleteModelButton->setEnabled(modelsDb_.size() > 0);
	ui->editModelButton->setEnabled(modelsDb_.size() > 0);
}

void StartMenu::onEditModelButtonClicked() {
	auto modelNameRowIndex = ui->modelsList->currentRow();
	if (ui->modelsList->count() == 0) {
		QMessageBox::information(this, "Модели", "В вашем списке пока нет моделей");
		return;
	} else if (modelNameRowIndex < 0) {
		QMessageBox::information(this, "Модели", "Выберите модель для редактирования");
		return;
	}
	auto modelName = ui->modelsList->currentItem()->text().toStdString();
	if (modelsDb_.count(modelName)) {
		auto model =  &modelsDb_.model(modelName);
		auto createModelDialog = new DecisionModelDialog(this, modelsDb_, model);
		auto res = createModelDialog->exec();
		if (res == QDialog::Accepted) {
			emit onEditDecisionModelDialogAccepted(createModelDialog, model);
		}
	}
}

void StartMenu::onEditDecisionModelDialogAccepted(const DecisionModelDialog *createModelDialog, DecisionModel *model) {

	ui->alternativesList->clear();
	for (const auto & altName : model->alternativesNames())
		ui->alternativesList->addItem(QString::fromStdString(altName));

	ui->criteriaList->clear();
	for (const auto  &criteriaName: model->criteriaNames())
		ui->criteriaList->addItem(QString::fromStdString(criteriaName));

}

void StartMenu::onModelListUpdate() {
	if (!ui->modelsList->count() > 0 || !ui->modelsList->currentItem())
		return;
	ui->alternativesList->clear();
	ui->criteriaList->clear();

	auto modelName = ui->modelsList->currentItem()->text().toStdString();
	if (modelsDb_.count(modelName)) {
		auto model = modelsDb_.model(modelName);

		for (auto &alternativeName: model.alternativesNames())
			ui->alternativesList->addItem(QString::fromStdString(alternativeName));
		for (auto &criterionName: model.criteriaNames())
			ui->criteriaList->addItem(QString::fromStdString(criterionName));

		ui->compareCriteriaButton->setEnabled(true);
		ui->compareAlternativesButton->setEnabled(true);
		ui->deleteModelButton->setEnabled(true);
		ui->editModelButton->setEnabled(true);
	}
}

void StartMenu::onDecisionModelDialogAccepted(const DecisionModelDialog *createModelDialog) {
	qDebug() << "Accepted DecisionModelDialog";
	DecisionModel decisionModel;
	auto modelName = createModelDialog->modelName();
	decisionModel.setDecisionName(modelName.toStdString());

	auto alternativesNames = createModelDialog->alternativesNames();
	auto criteriaNames = createModelDialog->criteriaNames();

	for (const auto &alternativeName: alternativesNames) {
		decisionModel.addAlternativeName(alternativeName.toStdString());
	}
	for (const auto &criterionName: criteriaNames) {
		decisionModel.addCriteriaName(criterionName.toStdString());
	}
	modelsDb_.addOrUpdateModel(decisionModel.modelName(), decisionModel);

	ui->modelsList->addItem(modelName);
	auto currentModelIndex = ui->modelsList->count() - 1;
	ui->modelsList->setCurrentRow(currentModelIndex);

	emit modelUpdated();
}

void StartMenu::onCompareAlternativesButtonClicked() {
	auto modelName = ui->modelsList->currentItem()->text().toStdString();

	if (ui->alternativesList->count() > 0) {
		auto &model = (modelsDb_.model(modelName));
		auto compareAlternativesDialog = new CompareAlternativesDialog(model, this);
		auto res = compareAlternativesDialog->exec();
		if (res == QDialog::Accepted) {
			if (model.criteriaComparisonMatrixIsInit() && model.alternativesComparisonsMatricesIsInit())
				switchState(eMode::eModelPrepared);
		}
	}
}

void StartMenu::onCompareCriteriaButtonClicked() {
	auto modelName = ui->modelsList->currentItem()->text().toStdString();
	if (ui->criteriaList->count() > 0) {
		auto &model = (modelsDb_.model(modelName));
		auto compareCriteriaDialog = new CompareCriteriaDialog(model, this);
		auto res = compareCriteriaDialog->exec();
		if (res == QDialog::Accepted) {
			if (model.criteriaComparisonMatrixIsInit() && model.alternativesComparisonsMatricesIsInit())
				switchState(eMode::eModelPrepared);
		}
	}
}

void StartMenu::onEstimateButtonClicked() {
	auto modelName = ui->modelsList->currentItem()->text().toStdString();
	auto model = modelsDb_.model(modelName);

	auto [ahp, gm, tropical] =
			std::tuple(ui->ahpCheckBox->isChecked(), ui->gmCheckBox->isChecked(), ui->tmCheckBox->isChecked());
	QString result;

	if (ahp) {
		model.performAhpMethod();
		ui->ahpLabel->setText(QString::fromStdString("Метод анализа иерархий\n\n\n" + model.ahpResult()));
	} else {
		ui->ahpLabel->clear();
	}

	if (gm) {
		model.performGmMethod();
		ui->gmLabel->setText(QString::fromStdString("Метод геометрических средних\n\n\n" + model.gmResult()));
	} else {
		ui->gmLabel->clear();
	}

	if (tropical) {
		model.performTropicalMethod();
		auto [best, worst] = model.tropicalResult();
		ui->tmBestLabel->setText(QString::fromStdString(
				"Метод log-чебышевской аппроксимации\nНаилучший дифференцирующий вектор\n\n" + best));
		ui->tmWorstLabel->setText(QString::fromStdString(
				"Метод log-чебышевской аппроксимации\nНаихудший дифференцирующий вектор\n\n" + worst));
	} else {
		ui->tmBestLabel->clear();
		ui->tmWorstLabel->clear();
	}
}

void StartMenu::onModelReady() {
}

void StartMenu::switchState(StartMenu::eMode newState) {
	switch (newState) {
		case eMode::eModelNotPrepared:
			ui->estimateButton->setEnabled(false);
			ui->ahpCheckBox->setEnabled(false);
			ui->gmCheckBox->setEnabled(false);
			ui->tmCheckBox->setEnabled(false);
			break;
		case eMode::eModelPrepared:
			ui->estimateButton->setEnabled(true);
			ui->ahpCheckBox->setEnabled(true);
			ui->gmCheckBox->setEnabled(true);
			ui->tmCheckBox->setEnabled(true);
	}
}
