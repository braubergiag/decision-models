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
	virtual void perform() = 0;

private:
	std::vector<MatrixT> alternatives_;
	FinalWeightT final_weights_;
	MatrixT criteria_;
};

