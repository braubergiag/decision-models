#pragma once

#include  <vector>
#include <string>
#include <Eigen/Core>
#include "ahp_decision_method.h"
#include "gm_decision_method.h"
#include "tropical_decision_method.h"

using ComparisionMatrixView = Eigen::Matrix<std::string,Dynamic,Dynamic>;



class DecisionModel
{
public:
    using ComparisonMatrixView = Eigen::Matrix<std::string,Dynamic,Dynamic>;


    DecisionModel() = default;
public:
    void addAlternative(const std::string &alternative);
    void addCriteria(const std::string &criteria);
public:
    void performTropicalMethod();
    void performAhpMethod();
    void performGmMethod();

    std::string ahpResult() const;
    std::string gmResult() const;
    std::pair<std::string, std::string> tropicalResult() const;

public:
    void setDecisionName(const string &decisionName);
    void setCriteriaNames(const vector<std::string> &criteriaNames);
    void setAlternativesNames(const vector<std::string> &alternativesNames);
    void setCriteriaComparisons(const MatrixXd &criteriaComparisons, const ComparisionMatrixView &criteriaMatrixView);


    void setAlternativesComparisons(const vector<Eigen::MatrixXd> &alternativesComparisons);
    void setAlternativesCompsAt(const Eigen::MatrixXd &alternativesComps,
                                const ComparisionMatrixView &alternativesCompsView, int index);

    const ComparisionMatrixView& compsViewAt(int index) const;
    const MatrixXd & compsAt(int index) const;
    bool compsIsInitAt(int index) const;
public:
    const string &decisionName() const;
    const vector<std::string> &criteriaNames() const;
    const vector<std::string> &alternativesNames() const;

    const MatrixXd &criteriaComparisons() const;
    const ComparisonMatrixView &criteriaComparisonsMatrixView() const;
    bool criteriaComparisonMatrixIsInit() const;
    bool alternativesComparisonsMatricesIsInit() const;

    const vector<Eigen::MatrixXd> &alternativesComparisons() const;

    int criteriaCount() const;
    int alternativesCount() const;

private:
    std::string decisionName_;
    std::vector<std::string> criteriaNames_;
    std::vector<std::string> alternativesNames_;

    ComparisonMatrixView criteriaComparisonsMatrixView_;
    Eigen::MatrixXd criteriaComparisons_;

    std::vector<Eigen::MatrixXd> alternativesComps_;
    std::vector<ComparisonMatrixView> alternativesCompsViews_;
    std::vector<bool> alternativesCompsIsInit_;


    bool criteriaComparisonMatrixIsInit_{false};
    bool alternativesComparisonsMatricesIsInit_{false};

    ahp_decision_method ahpDecisionMethod_;
    gm_decision_method gmDecisionMethod_;
    tropical_decision_method tropicalDecisionMethod_;

};

