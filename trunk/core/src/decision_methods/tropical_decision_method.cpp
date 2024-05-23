#include <numeric>
#include "../../include/decision_methods/tropical_decision_method.h"

tropical_decision_method::tropical_decision_method(const std::vector<MaxAlgMatrixXd> &alternatives,
												   const MaxAlgMatrixXd &criteria)
	: decision_method(alternatives, criteria) {
}

tropical_decision_method::tropical_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
												   const Eigen::MatrixXd &criteria)
	: decision_method(convert_alternatives(alternatives), tropical::to_MaxAlgMatrixXd(criteria)) {
}

std::vector<MaxAlgMatrixXd>
tropical_decision_method::convert_alternatives(const std::vector<Eigen::MatrixXd> &alternatives) const {
	std::vector<MaxAlgMatrixXd> converted_alternatives;
	for (const auto &alt: alternatives) {
		converted_alternatives.emplace_back(tropical::to_MaxAlgMatrixXd(alt));
	}
	return converted_alternatives;
}

void tropical_decision_method::perform() {
	auto D = optimal_weights_matrix(criteria(), spectral_radius(criteria()));
	auto v_weight_vectors = best_diff_weight_vectors(D, best_diff_weight_vector_indices(D));
	auto w = worst_diff_weight_vector(D);

	std::vector<MaxAlgVectorXd> best_alternatives_vectors;
	for (auto v: v_weight_vectors) {
		auto P = weighted_sum_pairwise_comparison_matrices(alternatives(), v);
		auto Q = build_alternatives_ratings_matrix(P);
		auto x = best_diff_alternatives_ratings_vectors(Q);
		best_alternatives_vectors.insert(best_alternatives_vectors.end(), x.begin(), x.end());
	}

	auto R = weighted_sum_pairwise_comparison_matrices(alternatives(), w);
	auto S = build_alternatives_ratings_matrix(R);
	auto y = worst_diff_alternatives_ratings_vector(S);

	set_final_weights({best_alternatives_vectors, y});
}

std::vector<int> tropical_decision_method::best_diff_weight_vector_indices(const MaxAlgMatrixXd &D) const {
	std::vector<int> vector_indices;
	double current_max = 0;
	for (auto i = 0; i < D.cols(); ++i) {
		auto norm_product = D.col(i).maxCoeff() * D.col(i).cwiseInverse().maxCoeff();
		if (current_max < norm_product) {
			vector_indices.clear();
			vector_indices.emplace_back(i);
			current_max = norm_product;
		} else if (current_max == norm_product) {
			vector_indices.emplace_back(i);
		}
	}
	return vector_indices;
}

std::vector<MaxAlgVectorXd> tropical_decision_method::best_diff_weight_vectors(const MaxAlgMatrixXd &D,
																			   std::vector<int> indices) const {
	std::vector<MaxAlgVectorXd> best_weight_vectors;
	for (auto index: indices) {
		auto v = D.col(index) * d(1, D.col(index).maxCoeff());
		best_weight_vectors.emplace_back(v);
	}
	remove_dominating_vectors(best_weight_vectors);
	return best_weight_vectors;
}

MaxAlgMatrixXd tropical_decision_method::optimal_weights_matrix(const MaxAlgMatrixXd &Criteria, double lambda) const {
	return kleene_star(d(1, lambda) * Criteria);
}

MaxAlgVectorXd tropical_decision_method::worst_diff_weight_vector(const MaxAlgMatrixXd &D) const {
	auto i = tropical::ones(D.rows());
	return (i.transpose() * D).cwiseInverse();
}

MaxAlgMatrixXd
tropical_decision_method::weighted_sum_pairwise_comparison_matrices(std::vector<MaxAlgMatrixXd> alternatives,
																	const MaxAlgVectorXd &v) {
	for (Eigen::Index i = 0, sz = v.size(); i < sz; ++i) {
		alternatives[i] *= v(i);
	}
	int alternatives_count = alternatives.front().rows();
	return std::accumulate(begin(alternatives), end(alternatives), tropical::eye(alternatives_count));
}

MaxAlgMatrixXd tropical_decision_method::build_alternatives_ratings_matrix(const MaxAlgMatrixXd &P) const {
	double mu = spectral_radius(P);
	MaxAlgMatrixXd Q = kleene_star(d(1, mu) * P);
	return Q;
}

std::vector<MaxAlgVectorXd>
tropical_decision_method::best_diff_alternatives_ratings_vectors(const MaxAlgMatrixXd &Q) const {
	auto vector_indices = best_diff_weight_vector_indices(Q);
	std::vector<MaxAlgVectorXd> best_vectors;
	for (auto i: vector_indices) {
		best_vectors.emplace_back(Q.col(i) * d(1, Q.col(i).sum()));
	}
	remove_dominating_vectors(best_vectors);
	return best_vectors;
}

MaxAlgVectorXd tropical_decision_method::worst_diff_alternatives_ratings_vector(const MaxAlgMatrixXd &S) const {
	auto i = tropical::ones(S.rows());
	return (i.transpose() * S).cwiseInverse();
}
