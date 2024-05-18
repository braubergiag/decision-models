#pragma once

#include "heuristic_decision_method.h"


class gm_decision_method : public heuristic_decision_method {
public:
	gm_decision_method() = default;
	gm_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const Eigen::MatrixXd &criteria);

public:
	void perform() override;
};
