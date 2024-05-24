#pragma once

#include <vector>
#include <Eigen/Dense>
#include <Eigen/Core>


template<typename MatrixT, typename VectorT, typename FinalWeightT = VectorT>
class decision_method {
public:
	decision_method() = default;
	decision_method(const std::vector<MatrixT> &alternatives, const MatrixT &criteria)
		: alternatives_(alternatives), criteria_(criteria) {}

public:
	int criteria_count() const { return criteria_.rows(); }
	int alternatives_count() const { return alternatives_.empty() ? 0 : alternatives_.front().rows(); }

public:
	const std::vector<MatrixT> &alternatives() const { return alternatives_; }
	const MatrixT &criteria() const { return criteria_; }

public:
	void set_criteria(const MatrixT &criteria) { criteria_ = criteria; }
	void set_final_weights(const FinalWeightT &final_weights) { final_weights_ = final_weights; }
	void set_alternatives(const std::vector<MatrixT> &alternatives) { alternatives_ = alternatives; }

public:
	const FinalWeightT &final_weights() const { return final_weights_; }
	VectorT normalize_weights(const VectorT &weights, double scale) const;
	virtual void perform() = 0;

private:
	std::vector<MatrixT> alternatives_;
	FinalWeightT final_weights_;
	MatrixT criteria_;
};
template<typename MatrixT, typename VectorT, typename FinalWeightT>
VectorT decision_method<MatrixT, VectorT, FinalWeightT>::normalize_weights(const VectorT &weights, double scale) const {
	VectorT normalized_weights = VectorT::Zero(weights.size());
	for (auto i = 0; i < weights.size(); ++i) {
		normalized_weights(i) = weights(i) / scale;
	}
	return normalized_weights;
}
