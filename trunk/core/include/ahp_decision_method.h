#pragma once

#include <Eigen/Dense>
#include <vector>
#include "heuristic_decision_method.h"

using Eigen::MatrixXd;

class ahp_decision_method : public heuristic_decision_method {

public:
	ahp_decision_method() = default;
	ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const MatrixXd &criteria);
	void perform() override;

public:
	Eigen::MatrixXd weight_matrix(const std::vector<Eigen::MatrixXcd> &alternatives_main_eigen_vectors) const;
	Eigen::VectorXd weight_vector(const Eigen::VectorXcd &criteria_main_eigen_vector,
								  const std::vector<Eigen::MatrixXcd> &alternatives_main_eigen_vectors) const;
	Eigen::MatrixXcd main_eigenvector(const MatrixXd &matrix) const;
};
