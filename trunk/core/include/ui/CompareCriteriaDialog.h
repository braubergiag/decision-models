#pragma once
#include <QDialog>
#include <QTableWidget>
#include <Eigen/Core>
#include "../DecisionModel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class CompareCriteriaDialog; }
QT_END_NAMESPACE

class CompareCriteriaDialog : public QDialog {
Q_OBJECT

public:
    explicit CompareCriteriaDialog(DecisionModel &decisionModel, QWidget *parent);
    ~CompareCriteriaDialog() override;

private:
    void initCriteriaTableWidget();
    void loadCriteriaTableWidget();
private slots:
    void onCellChanged(int row, int column);
    void onButtonBoxAccepted();
    void onButtonBoxRejected();

private:

    DecisionModel & decisionModel_;
    Eigen::MatrixXd criteriaComparisons_;
    ComparisionMatrixView criteriaMatrixView_;


    int rowCount_;
    int columnCount_;
    const double kDefaultValue{1.};
    const QString kDefaultValueView{"1"};
    Ui::CompareCriteriaDialog *ui;
};

