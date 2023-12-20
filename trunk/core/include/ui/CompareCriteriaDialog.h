#pragma once
#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class CompareCriteriaDialog; }
QT_END_NAMESPACE

class CompareCriteriaDialog : public QDialog {
Q_OBJECT

public:
    explicit CompareCriteriaDialog(QWidget *parent = nullptr);

    ~CompareCriteriaDialog() override;

private:
    Ui::CompareCriteriaDialog *ui;
};

