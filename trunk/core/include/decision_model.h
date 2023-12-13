#pragma once

#include  <vector>
#include <string>
#include "ahp_decision_method.h"
#include "gm_decision_method.h"
#include "tropical_decision_method.h"
class decision_model
{
public:
    decision_model();
private:
    std::vector<std::string> criteria_names_;
    std::vector<std::string> alternatives_names_;

    ahp_decision_method ahp;
    gm_decision_method gm;
    tropical_decision_method tr;

};

