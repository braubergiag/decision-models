//
// Created by igor on 26.12.22.
//

#ifndef TROPICAL_GMDECISIONMETHOD_H
#define TROPICAL_GMDECISIONMETHOD_H

#include "heuristic_decision_method.h"


class gm_decision_method  : public heuristic_decision_method{
public:
    void perform() override;

public:
    gm_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const Eigen::MatrixXd &criteria);
};


#endif //TROPICAL_GMDECISIONMETHOD_H
