#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QVector>
#include <QString>
#include "../DecisionModelsDB.h"
QT_BEGIN_NAMESPACE
namespace Ui { class DecisionModelDialog; }
QT_END_NAMESPACE

class DecisionModelDialog : public QDialog {
    Q_OBJECT

public:
    explicit DecisionModelDialog(const DecisionModelsDB &modelsDb, QWidget *parent = nullptr);
    ~DecisionModelDialog() override;

private slots:
    void onAddAlternativeButtonClicked();
    void onAddCriteriaButtonClicked();
    void onButtonBoxAccepted();
    void onButtonBoxRejected();

public:
    const QVector<QString> &alternativesNames() const;
    const QVector<QString> &criteriaNames() const;

private:
    QString decisionName_;
public:
    const QString &decisionName() const;

private:
    const int kMinAlternativesCount{2};
    const int kMinCriteriaCount{1};
    const DecisionModelsDB & modelsDb_;
    QVector<QString> alternativesNames_;
    QVector<QString> criteriaNames_;
    QVector<QString> existingModelNames_;
    Ui::DecisionModelDialog *ui;
};


