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
