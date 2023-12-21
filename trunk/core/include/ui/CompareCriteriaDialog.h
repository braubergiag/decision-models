#pragma once
#include <QDialog>
#include <QTableWidget>
#include <Eigen/Core>

QT_BEGIN_NAMESPACE
namespace Ui { class CompareCriteriaDialog; }
QT_END_NAMESPACE

class CompareCriteriaDialog : public QDialog {
Q_OBJECT

public:
    explicit CompareCriteriaDialog(QWidget *parent, std::vector<std::string> criteriaNames);

    ~CompareCriteriaDialog() override;

private slots:
    void onCellChanged(int row, int column);
    void onButtonBoxAccepted();

private:
   std::vector<std::string> criteriaNames_;
    Eigen::MatrixXd criteriaComparisons_;
    int rowCount_;
    int columnCount_;
    Ui::CompareCriteriaDialog *ui;
};

