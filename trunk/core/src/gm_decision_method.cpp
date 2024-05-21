#include <algorithm>
#include "../include/gm_decision_method.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

gm_decision_method::gm_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
									   const Eigen::MatrixXd &criteria)
	: decision_method(alternatives, criteria) {
}

void gm_decision_method::perform() {
	const int alter_num = alternatives_count();
	const int criter_num = criteria_count();
	MatrixXd matrix_weights(alter_num, criter_num), matrix_powers(alter_num, criter_num),
			matrix_norm_weights(alter_num, criter_num);

	VectorXd crit_vector = VectorXd::Ones(criter_num);
	VectorXd final_weights = VectorXd::Ones(alter_num);

	for (int i = 0; i < criter_num; ++i) {
		crit_vector(i) = pow(criteria().row(i).prod(), 1. / criter_num);
		for (int j = 0; j < alter_num; ++j) {
			matrix_weights(j, i) = pow(alternatives().at(i).row(j).prod(), 1. / alter_num);
		}
	}

	double criteria_vector_sum = crit_vector.sum();
	std::transform(crit_vector.begin(), crit_vector.end(), crit_vector.begin(),
				   [criteria_vector_sum](const auto &w) { return w / criteria_vector_sum; });


	for (int i = 0; i < criter_num; ++i) {
		for (int j = 0; j < alter_num; ++j) {
			matrix_powers(j, i) = pow(matrix_weights(j, i), crit_vector(i));
		}
	}
	for (int i = 0; i < criter_num; ++i) {
		for (int j = 0; j < alter_num; ++j)
			final_weights(j) *= matrix_powers(j, i);
	}

	double final_vector_sum = final_weights.maxCoeff();
	std::transform(final_weights.begin(), final_weights.end(), final_weights.begin(),
				   [final_vector_sum](auto &w) { return w / final_vector_sum; });


	set_final_weights(final_weights);
}
