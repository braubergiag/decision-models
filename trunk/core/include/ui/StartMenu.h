#pragma once

#include <QWidget>
#include <QPushButton>
#include "DecisionModelDialog.h"
#include "CompareAlternativesDialog.h"
#include "CompareCriteriaDialog.h"
#include "../DecisionModelsDB.h"
#include <memory>
QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QWidget {
Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);

    ~StartMenu() override;
signals:
    void decisionModelDialogAccepted();
    void modelUpdated();


private slots:
    void onCreateModelButtonClicked();
    void onDeleteModelButtonClicked();
    void onEditModelButtonClicked();
    void onCompareAlternativesButtonClicked();
    void onCompareCriteriaButtonClicked();
    void onDecisionModelDialogAccepted(const DecisionModelDialog *createModelDialog, const std::string &oldModelName = {});
    void onModelListUpdate();
private:
    DecisionModelsDB modelsDb_;
    Ui::StartMenu *ui;
};

