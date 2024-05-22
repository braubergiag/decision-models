#include <numeric>
#include "../../include/decision_methods/tropical_decision_method.h"

tropical_decision_method::tropical_decision_method(const std::vector<MaxAlgMatrixXd> &alternatives,
												   const MaxAlgMatrixXd &criteria)
	: alternatives_(alternatives), criteria_(criteria) {
}

tropical_decision_method::tropical_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
												   const Eigen::MatrixXd &criteria) {
	alternatives_.resize(alternatives.size());
	for (int i = 0; i < alternatives_.size(); ++i) {
		auto &alt = alternatives_.at(i);
		alt.resize(alternatives.front().rows(), alternatives.front().cols());
		for (int row = 0; row < alt.rows(); ++row) {
			for (int column = 0; column < alt.cols(); ++column) {
				alt(row, column) = alternatives.at(i)(row, column);
			}
		}
	}
	criteria_.resize(criteria.rows(), criteria.cols());
	for (int row = 0; row < criteria_.rows(); ++row) {
		for (int column = 0; column < criteria_.cols(); ++column) {
			criteria_(row, column) = criteria(row, column);
		}
	}
}

const std::vector<MaxAlgMatrixXd> &tropical_decision_method::alternatives() const {
	return alternatives_;
}

void tropical_decision_method::set_alternatives(const std::vector<MaxAlgMatrixXd> &alternatives) {
	alternatives_ = alternatives;
}

const MaxAlgMatrixXd &tropical_decision_method::criteria() const {
	return criteria_;
}

void tropical_decision_method::set_criteria(const MaxAlgMatrixXd &criteria) {
	criteria_ = criteria;
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
	auto I = MaxAlgVectorXd::Ones(D.rows()).transpose();
	return (I * D).array().inverse();
}

MaxAlgMatrixXd
tropical_decision_method::weighted_sum_pairwise_comparison_matrices(std::vector<MaxAlgMatrixXd> alternatives,
																	const MaxAlgVectorXd &v) const {
	for (size_t i = 0, sz = v.size(); i < sz; ++i) {
		alternatives[i] *= v(i);
	}

	MaxAlgMatrixXd P = MaxAlgMatrixXd::Identity(alternatives.front().rows(), alternatives.front().cols());
	return std::accumulate(begin(alternatives), end(alternatives), P);
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
	auto i_tr = MaxAlgVectorXd::Ones(S.rows()).transpose();
	return (i_tr * S).array().inverse().transpose();
}


void tropical_decision_method::set_final_weights(
		const std::pair<std::vector<MaxAlgVectorXd>, MaxAlgVectorXd> &final_weights) {
	final_weights_ = final_weights;
}
const std::pair<std::vector<MaxAlgVectorXd>, MaxAlgVectorXd> &tropical_decision_method::final_weights() const {
	return final_weights_;
}
