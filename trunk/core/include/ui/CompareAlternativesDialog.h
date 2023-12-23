#pragma once
#include <QDialog>
#include <Eigen/Core>
#include "../DecisionModel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class CompareAlternativesDialog; }
QT_END_NAMESPACE

class CompareAlternativesDialog : public QDialog {
Q_OBJECT

public:
    explicit CompareAlternativesDialog(DecisionModel &decisionModel, QWidget *parent = nullptr);

    ~CompareAlternativesDialog() override;
public:

public slots:
    void onCriteriaChanged(int index);
    void onCellChanged(int row, int column);

private:
    void initMatrixViews();
    void initTableWidget();
    void initComboBoxItems();

private:
    DecisionModel & decisionModel_;
    QList<QString> criteriaNames_;
    std::vector<ComparisionMatrixView> matrixViews_;
    std::vector<Eigen::MatrixXd> matrixValues_;
    std::vector<bool> matrixIsInited_;


    int rowCount_;
    int columnCount_;
    int lastActiveIndex_{0};

private:
    Ui::CompareAlternativesDialog *ui;
};


