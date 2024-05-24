#include <algorithm>
#include "../../include/decision_methods/gm_decision_method.h"
#include "../../include/decision_methods/utils.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

gm_decision_method::gm_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
									   const Eigen::MatrixXd &criteria)
	: decision_method(alternatives, criteria) {
}

void gm_decision_method::perform() {
	using utils::d;

	const auto n_alternatives = alternatives_count();
	const auto n_criteria = criteria_count();
	MatrixXd matrix_weights(n_alternatives, n_criteria);
	MatrixXd matrix_powers(n_alternatives, n_criteria);
	MatrixXd matrix_norm_weights(n_alternatives, n_criteria);

	VectorXd criteria_weight_vector = VectorXd::Ones(n_criteria);
	VectorXd final_weights = VectorXd::Ones(n_alternatives);

	for (auto i = 0; i < n_criteria; ++i) {
		criteria_weight_vector(i) = pow(criteria().row(i).prod(), d(1, n_criteria));
		for (auto j = 0; j < n_alternatives; ++j) {
			matrix_weights(j, i) = pow(alternatives().at(i).row(j).prod(), d( 1, n_alternatives));
		}
	}

	criteria_weight_vector = normalize_weights(criteria_weight_vector, criteria_weight_vector.sum());

	for (auto i = 0; i < n_criteria; ++i) {
		for (auto j = 0; j < n_alternatives; ++j) {
			matrix_powers(j, i) = pow(matrix_weights(j, i), criteria_weight_vector(i));
		}
	}

	for (auto i = 0; i < n_criteria; ++i) {
		for (auto j = 0; j < n_alternatives; ++j)
			final_weights(j) *= matrix_powers(j, i);
	}

	set_final_weights(normalize_weights(final_weights, final_weights.maxCoeff()));
}
