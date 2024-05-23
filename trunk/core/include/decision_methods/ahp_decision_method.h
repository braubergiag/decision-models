#pragma once

#include <Eigen/Dense>
#include <vector>
#include "decision_method.h"

class ahp_decision_method : public decision_method<Eigen::MatrixXd, Eigen::VectorXd> {
public:
	ahp_decision_method() = default;
	ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const Eigen::MatrixXd &criteria);

public:
	Eigen::MatrixXd weight_matrix(const std::vector<Eigen::MatrixXd> &alternatives_main_eigen_vectors) const;

	Eigen::VectorXd weight_vector(const Eigen::VectorXd &criteria_main_eigen_vector,
								  const std::vector<Eigen::MatrixXd> &alternatives_main_eigen_vectors) const;

	Eigen::MatrixXd main_eigenvector(const Eigen::MatrixXd &matrix) const;

public:
	void perform() override;
};
