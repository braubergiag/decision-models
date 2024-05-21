#pragma once

#include <utility>
#include "decision_method.h"
#include "tropical.h"

class tropical_decision_method : public decision_method {

public:
	tropical_decision_method() = default;
	tropical_decision_method(const std::vector<MaxAlgMatrixXd> &alternatives, const MaxAlgMatrixXd &criteria);
	tropical_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const Eigen::MatrixXd &criteria);
	void perform() override;

public:
	const std::vector<MaxAlgMatrixXd> &alternatives() const;
	const MaxAlgMatrixXd &criteria() const;
	const std::pair<MaxAlgMatrixXd, MaxAlgMatrixXd> &final_weights() const;

public:
	void set_criteria(const MaxAlgMatrixXd &criteria);
	void set_alternatives(const std::vector<MaxAlgMatrixXd> &alternatives);

public:
	int best_differentiating_weight_vector_index(const MaxAlgMatrixXd &D) const;
	MaxAlgVectorXd best_differentiating_weight_vector(const MaxAlgMatrixXd &D, int index) const;
	MaxAlgVectorXd worst_differentiating_weight_vector(const MaxAlgMatrixXd &D) const;
	MaxAlgMatrixXd construction_generating_matrix_optimal_weights(const MaxAlgMatrixXd &Criteria, double lambda) const;
	MaxAlgMatrixXd computing_weighted_sum_pairwise_comparison_matrices(std::vector<MaxAlgMatrixXd> alternatives,
																	   const MaxAlgVectorXd &v) const;
	MaxAlgMatrixXd build_generating_matrix_optimal_ratings_alternatives(const MaxAlgMatrixXd &P) const;
	MaxAlgMatrixXd calc_best_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &Q) const;
	MaxAlgMatrixXd calc_worst_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &S) const;

private:
	void set_final_weights(const std::pair<MaxAlgMatrixXd, MaxAlgMatrixXd> &final_weights);

private:
	std::vector<MaxAlgMatrixXd> alternatives_;
	std::pair<MaxAlgMatrixXd, MaxAlgMatrixXd> final_weights_;
	MaxAlgMatrixXd criteria_;
};
