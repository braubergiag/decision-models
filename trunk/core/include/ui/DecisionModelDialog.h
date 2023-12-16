#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QVector>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui { class DecisionModelDialog; }
QT_END_NAMESPACE

class DecisionModelDialog : public QDialog {
    Q_OBJECT

public:
    explicit DecisionModelDialog(QWidget *parent = nullptr);
    ~DecisionModelDialog() override;

private slots:
    void onAddAlternativeButtonClicked();
    void onAddCriteriaButtonClicked();
    void onButtonBoxAccepted();

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
    QVector<QString> alternativesNames_;
    QVector<QString> criteriaNames_;
    Ui::DecisionModelDialog *ui;
};


