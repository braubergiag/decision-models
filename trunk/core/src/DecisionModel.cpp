#include "../include/DecisionModel.h"

void DecisionModel::addAlternative(const std::string &alternative) {
    alternativesNames_.emplace_back(alternative);
}

void DecisionModel::addCriteria(const std::string &criteria) {
    criteriaNames_.emplace_back(criteria);

}

void DecisionModel::set_decision_name(const string &decisionName) {
    decisionName_ = decisionName;
}
