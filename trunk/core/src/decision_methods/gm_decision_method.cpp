#include <algorithm>
#include "../../include/decision_methods/gm_decision_method.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

gm_decision_method::gm_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
									   const Eigen::MatrixXd &criteria)
	: decision_method(alternatives, criteria) {
}

void gm_decision_method::perform() {
	const int n_alternatives = alternatives_count();
	const int n_criteria = criteria_count();
	MatrixXd matrix_weights(n_alternatives, n_criteria);
	MatrixXd matrix_powers(n_alternatives, n_criteria);
	MatrixXd matrix_norm_weights(n_alternatives, n_criteria);

	VectorXd criteria_weight_vector = VectorXd::Ones(n_criteria);
	VectorXd final_weights = VectorXd::Ones(n_alternatives);

	for (int i = 0; i < n_criteria; ++i) {
		criteria_weight_vector(i) = pow(criteria().row(i).prod(), 1. / n_criteria);
		for (int j = 0; j < n_alternatives; ++j) {
			matrix_weights(j, i) = pow(alternatives().at(i).row(j).prod(), 1. / n_alternatives);
		}
	}

	double criteria_vector_sum = criteria_weight_vector.sum();
	for (auto &criteria_weight: criteria_weight_vector)
		criteria_weight /= criteria_vector_sum;

	for (int i = 0; i < n_criteria; ++i) {
		for (int j = 0; j < n_alternatives; ++j) {
			matrix_powers(j, i) = pow(matrix_weights(j, i), criteria_weight_vector(i));
		}
	}

	for (int i = 0; i < n_criteria; ++i) {
		for (int j = 0; j < n_alternatives; ++j)
			final_weights(j) *= matrix_powers(j, i);
	}

	auto final_weights_max_coeff = final_weights.maxCoeff();
	for (auto &weight: final_weights)
		weight /= final_weights_max_coeff;

	set_final_weights(final_weights);
}
