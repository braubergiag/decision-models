#pragma once
#include <QDialog>
#include <Eigen/Core>

QT_BEGIN_NAMESPACE
namespace Ui { class CompareAlternativesDialog; }
QT_END_NAMESPACE

class CompareAlternativesDialog : public QDialog {
Q_OBJECT

public:
    explicit CompareAlternativesDialog(QWidget *parent = nullptr);

    ~CompareAlternativesDialog() override;

private:
    std::vector<Eigen::MatrixXd> alternativesComparisons_;
    Ui::CompareAlternativesDialog *ui;
};


