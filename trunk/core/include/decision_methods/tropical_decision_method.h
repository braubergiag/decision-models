#pragma once

#include <utility>
#include "decision_method.h"
#include "tropical.h"

using tropical::d;
using tropical::MaxAlgMatrixXd;
using tropical::MaxAlgVectorXd;

class tropical_decision_method {
	using FinalWeights = std::pair<std::vector<MaxAlgVectorXd>, MaxAlgVectorXd>;

public:

	tropical_decision_method() = default;
	tropical_decision_method(const std::vector<MaxAlgMatrixXd> &alternatives, const MaxAlgMatrixXd &criteria);
	tropical_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const Eigen::MatrixXd &criteria);
	void perform();

public:
	const std::vector<MaxAlgMatrixXd> &alternatives() const;
	const MaxAlgMatrixXd &criteria() const;
	const FinalWeights &final_weights() const;

public:
	void set_criteria(const MaxAlgMatrixXd &criteria);
	void set_alternatives(const std::vector<MaxAlgMatrixXd> &alternatives);

public:
	std::vector<int> best_diff_weight_vector_indices(const MaxAlgMatrixXd &D) const;
	std::vector<MaxAlgVectorXd> best_diff_weight_vectors(const MaxAlgMatrixXd &D, std::vector<int> indices) const;
	MaxAlgVectorXd worst_diff_weight_vector(const MaxAlgMatrixXd &D) const;
	MaxAlgMatrixXd optimal_weights_matrix(const MaxAlgMatrixXd &Criteria, double lambda) const;
	MaxAlgMatrixXd weighted_sum_pairwise_comparison_matrices(std::vector<MaxAlgMatrixXd> alternatives,
															 const MaxAlgVectorXd &v);
	MaxAlgMatrixXd build_alternatives_ratings_matrix(const MaxAlgMatrixXd &P) const;
	std::vector<MaxAlgVectorXd> best_diff_alternatives_ratings_vectors(const MaxAlgMatrixXd &Q) const;
	MaxAlgVectorXd worst_diff_alternatives_ratings_vector(const MaxAlgMatrixXd &S) const;

private:
	void set_final_weights(const FinalWeights &final_weights);

private:
	std::vector<MaxAlgMatrixXd> alternatives_;
	FinalWeights final_weights_;
	MaxAlgMatrixXd criteria_;
};
