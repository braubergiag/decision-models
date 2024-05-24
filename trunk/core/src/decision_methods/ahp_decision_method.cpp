#include <Eigen/Eigenvalues>
#include "../../include/decision_methods/ahp_decision_method.h"

ahp_decision_method::ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
										 const Eigen::MatrixXd &criteria)
	: decision_method(alternatives, criteria) {
}

Eigen::MatrixXd ahp_decision_method::main_eigenvector(const Eigen::MatrixXd &matrix) const {
	Eigen::EigenSolver<Eigen::MatrixXd> eigen_solver(matrix);
	Eigen::VectorXd eigen_vector = eigen_solver.eigenvectors().col(0).real();
	eigen_vector = normalize_weights(eigen_vector.cwiseAbs(), eigen_vector.cwiseAbs().sum());
	return eigen_vector.real();
}

Eigen::MatrixXd
ahp_decision_method::weight_matrix(const std::vector<Eigen::MatrixXd> &alternatives_main_eigen_vectors) const {

	Eigen::MatrixXd weights(alternatives_count(), criteria_count());
	for (int i = 0; i < criteria_count(); ++i) {
		for (int j = 0; j < alternatives_count(); ++j) {
			weights(j, i) = alternatives_main_eigen_vectors.at(i).coeff(j);
		}
	}
	return weights;
}

Eigen::VectorXd
ahp_decision_method::weight_vector(const Eigen::VectorXd &criteria_main_eigen_vector,
								   const std::vector<Eigen::MatrixXd> &alternatives_main_eigen_vectors) const {
	Eigen::VectorXd weights = weight_matrix(alternatives_main_eigen_vectors) * criteria_main_eigen_vector;
	return normalize_weights(weights, weights.maxCoeff());
}

void ahp_decision_method::perform() {
	Eigen::VectorXd criteria_main_eigen_vector = main_eigenvector(criteria());
	std::vector<Eigen::MatrixXd> alternatives_main_eigen_vectors;
	for (const auto &alternative: alternatives()) {
		alternatives_main_eigen_vectors.emplace_back(main_eigenvector(alternative));
	}

	set_final_weights(weight_vector(criteria_main_eigen_vector, alternatives_main_eigen_vectors));
}
