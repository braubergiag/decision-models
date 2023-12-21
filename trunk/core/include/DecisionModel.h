#pragma once

#include  <vector>
#include <string>
#include <Eigen/Core>
#include "ahp_decision_method.h"
#include "gm_decision_method.h"
#include "tropical_decision_method.h"
class DecisionModel
{
public:
    DecisionModel() = default;
public:
    void addAlternative(const std::string &alternative);
    void addCriteria(const std::string &criteria);
public:
    void setDecisionName(const string &decisionName);
    void setCriteriaNames(const vector<std::string> &criteriaNames);
    void setAlternativesNames(const vector<std::string> &alternativesNames);
    void setCriteriaComparisons(const MatrixXd &criteriaComparisons);

public:
    const string &decisionName() const;
    const vector<std::string> &criteriaNames() const;
    const vector<std::string> &alternativesNames() const;

    const MatrixXd &criteriaComparisons() const;

private:
    std::string decisionName_;
    std::vector<std::string> criteriaNames_;
    std::vector<std::string> alternativesNames_;

    Eigen::MatrixXd criteriaComparisons_;
    std::vector<Eigen::MatrixXd> alternativesComparisons_;

    ahp_decision_method ahp;
    gm_decision_method gm;
    tropical_decision_method tr;

};

