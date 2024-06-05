#pragma once

#include <decision_method.h>

class gm_decision_method : public decision_method<typename Eigen::MatrixXd, typename Eigen::VectorXd> {
public:
	gm_decision_method() = default;
	gm_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const Eigen::MatrixXd &criteria);

public:
	void perform() override;
};
