#pragma once

#include  <vector>
#include <string>
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
    const string &decisionName() const;
public:
    void setDecisionName(const string &decisionName);

private:
    std::string decisionName_;
    std::vector<std::string> criteriaNames_;
public:
    const vector<std::string> &criteriaNames() const;

    const vector<std::string> &alternativesNames() const;

private:
    std::vector<std::string> alternativesNames_;

    ahp_decision_method ahp;
    gm_decision_method gm;
    tropical_decision_method tr;

};

