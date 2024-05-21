#pragma once

#include <vector>
#include <Eigen/Dense>
#include <Eigen/Core>


class decision_method {
public:
	decision_method() = default;
	decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const Eigen::MatrixXd &criteria);

public:
	int criteria_count() const;
	int alternatives_count() const;

public:
	const std::vector<Eigen::MatrixXd> &alternatives() const;
	const Eigen::MatrixXd &criteria() const;

public:
	void set_criteria(const Eigen::MatrixXd &criteria);
	void set_final_weights(const Eigen::VectorXd &final_weights);
	void set_alternatives(const std::vector<Eigen::MatrixXd> &alternatives);

public:
	const Eigen::VectorXd &final_weights() const;
	virtual void perform() = 0;

private:
	std::vector<Eigen::MatrixXd> alternatives_;
	Eigen::VectorXd final_weights_;
	Eigen::MatrixXd criteria_;
};
