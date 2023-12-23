#include "../include/DecisionModel.h"

void DecisionModel::addAlternative(const std::string &alternative) {
    alternativesNames_.emplace_back(alternative);
}

void DecisionModel::addCriteria(const std::string &criteria) {
    criteriaNames_.emplace_back(criteria);

}

void DecisionModel::setDecisionName(const string &decisionName) {
    decisionName_ = decisionName;
}

const string &DecisionModel::decisionName() const {
    return decisionName_;
}

const vector<std::string> &DecisionModel::criteriaNames() const {
    return criteriaNames_;
}

const vector<std::string> &DecisionModel::alternativesNames() const {
    return alternativesNames_;
}

void DecisionModel::setCriteriaNames(const vector<std::string> &criteriaNames) {
    criteriaNames_ = criteriaNames;
}

void DecisionModel::setAlternativesNames(const vector<std::string> &alternativesNames) {
    alternativesNames_ = alternativesNames;
}

const MatrixXd &DecisionModel::criteriaComparisons() const {
    return criteriaComparisons_;
}

void DecisionModel::setCriteriaComparisons(const MatrixXd &criteriaComparisons,
                                           const ComparisionMatrixView &criteriaMatrixView) {
    criteriaComparisons_ = criteriaComparisons;
    criteriaComparisonsMatrixView_ = criteriaMatrixView;
    criteriaComparisonMatrixIsInit_ = true;
}

const vector<Eigen::MatrixXd> &DecisionModel::alternativesComparisons() const {
    return alternativesComparisons_;
}

void DecisionModel::setAlternativesComparisons(const vector<Eigen::MatrixXd> &alternativesComparisons) {
    alternativesComparisons_ = alternativesComparisons;
}

int DecisionModel::criteriaCount() const {
    return criteriaNames_.size();
}

int DecisionModel::alternativesCount() const {
    return alternativesNames_.size();
}

bool DecisionModel::criteriaComparisonMatrixIsInit() const {
    return criteriaComparisonMatrixIsInit_;
}

const DecisionModel::ComparisonMatrixView &DecisionModel::criteriaComparisonsMatrixView() const {
    return criteriaComparisonsMatrixView_;
}
