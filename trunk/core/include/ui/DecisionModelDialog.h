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
    void on_addAlternative_clicked();

    void on_addCriteria_clicked();

    void on_buttonBox_accepted();

public:
    const QVector<QString> &alternativesNames() const;
    const QVector<QString> &criteriaNames() const;

private:
    QVector<QString> alternativesNames_;

    QVector<QString> criteriaNames_;
    Ui::DecisionModelDialog *ui;
};


