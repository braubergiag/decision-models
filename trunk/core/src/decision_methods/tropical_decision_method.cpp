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
	auto D = construction_generating_matrix_optimal_weights(criteria(), spectral_radius(criteria()));
	auto v = best_differentiating_weight_vector(D,  best_differentiating_weight_vector_index(D));
	auto w = worst_differentiating_weight_vector(D);

	auto P = computing_weighted_sum_pairwise_comparison_matrices(alternatives(), v);
	auto Q = build_generating_matrix_optimal_ratings_alternatives(P);
	auto x = calc_best_differentiating_vector_ratings_alternatives(Q);

	auto R = computing_weighted_sum_pairwise_comparison_matrices(alternatives(), w);
	auto S = build_generating_matrix_optimal_ratings_alternatives(R);
	auto y = calc_worst_differentiating_vector_ratings_alternatives(S);

	set_final_weights(std::make_pair(x, y));
}

int tropical_decision_method::best_differentiating_weight_vector_index(const MaxAlgMatrixXd &D) const {

	auto i_tr = MaxAlgVectorXd::Ones(D.rows()).transpose();
	double current_max = 0;
	int vector_idx = 0;
	for (auto i = 0; i < D.cols(); ++i) {
		MaxAlgMatrixXd x = D.col(i);
		MaxAlgMatrixXd x_ = D.col(i).cwiseInverse();
		auto r1 = ((i_tr * x) * (i_tr * x_));
		if (current_max < r1(0).scalar) {
			vector_idx = i;
			current_max = r1(0).scalar;
		}
	}
	return vector_idx;
}

MaxAlgVectorXd tropical_decision_method::best_differentiating_weight_vector(const MaxAlgMatrixXd &D, int index) const {
	return D.col(index) * d(1, D.col(index).sum());
}

MaxAlgMatrixXd tropical_decision_method::construction_generating_matrix_optimal_weights(const MaxAlgMatrixXd &Criteria,
																						double lambda) const {
	return kleene_star(d(1, lambda) * Criteria);
}

MaxAlgVectorXd tropical_decision_method::worst_differentiating_weight_vector(const MaxAlgMatrixXd &D) const {
	auto I = MaxAlgVectorXd::Ones(D.rows()).transpose();
	return (I * D).array().inverse();
}

MaxAlgMatrixXd
tropical_decision_method::computing_weighted_sum_pairwise_comparison_matrices(std::vector<MaxAlgMatrixXd> alternatives,
																			  const MaxAlgVectorXd &v) const {
	for (size_t i = 0, sz = v.size(); i < sz; ++i) {
		alternatives[i] *= v(i);
	}

	MaxAlgMatrixXd P = MaxAlgMatrixXd::Identity(alternatives.front().rows(), alternatives.front().cols());
	return std::accumulate(begin(alternatives), end(alternatives), P);
}

MaxAlgMatrixXd
tropical_decision_method::build_generating_matrix_optimal_ratings_alternatives(const MaxAlgMatrixXd &P) const {
	double mu = spectral_radius(P);
	MaxAlgMatrixXd Q = kleene_star(d(1, mu) * P);
	return Q;
}

MaxAlgMatrixXd
tropical_decision_method::calc_best_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &Q) const {
	int i = best_differentiating_weight_vector_index(Q);
	return Q.col(i) * d(1, Q.col(i).sum());
}

MaxAlgMatrixXd
tropical_decision_method::calc_worst_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &S) const {
	auto i_tr = MaxAlgVectorXd::Ones(S.rows()).transpose();
	return (i_tr * S).array().inverse().transpose();
}

const std::pair<MaxAlgMatrixXd, MaxAlgMatrixXd> &tropical_decision_method::final_weights() const {
	return final_weights_;
}

void tropical_decision_method::set_final_weights(const std::pair<MaxAlgMatrixXd, MaxAlgMatrixXd> &final_weights) {
	final_weights_ = final_weights;
}
