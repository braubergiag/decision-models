#include <Eigen/Eigenvalues>
#include <ahp_decision_method.h>

ahp_decision_method::ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
										 const Eigen::MatrixXd &criteria)
	: decision_method(alternatives, criteria) {
}

Eigen::MatrixXd ahp_decision_method::main_eigenvector(const Eigen::MatrixXd &matrix) const {
	Eigen::EigenSolver<Eigen::MatrixXd> eigen_solver(matrix);
	Eigen::VectorXd eigen_values = eigen_solver.eigenvalues().real();
	Eigen::MatrixXd eigen_vectors = eigen_solver.eigenvectors().real();

	int max_index{0};
	eigen_values.maxCoeff(&max_index);
	Eigen::VectorXd eigen_vector = eigen_vectors.col(max_index).cwiseAbs();
	eigen_vector = normalize_weights(eigen_vector, eigen_vector.sum());
	return eigen_vector;
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
	std::vector<Eigen::MatrixXd> alternatives_main_eigen_vectors;
	for (const auto &alternative: alternatives()) {
		alternatives_main_eigen_vectors.emplace_back(main_eigenvector(alternative));
	}
	Eigen::VectorXd criteria_main_eigen_vector = main_eigenvector(criteria());
	set_final_weights(weight_vector(criteria_main_eigen_vector, alternatives_main_eigen_vectors));
}
