#include "../../include/decision_methods/decision_method.h"

decision_method::decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
													 const Eigen::MatrixXd &criteria)
	: alternatives_(alternatives), criteria_(criteria) {
}

const std::vector<Eigen::MatrixXd> &decision_method::alternatives() const {
	return alternatives_;
}

void decision_method::set_alternatives(const std::vector<Eigen::MatrixXd> &alternatives) {
	alternatives_ = alternatives;
}

const Eigen::MatrixXd &decision_method::criteria() const {
	return criteria_;
}

void decision_method::set_criteria(const Eigen::MatrixXd &criteria) {
	criteria_ = criteria;
}

int decision_method::criteria_count() const {
	return alternatives_.size();
}

int decision_method::alternatives_count() const {
	return alternatives_.at(0).rows();
}

const Eigen::VectorXd &decision_method::final_weights() const {
	return final_weights_;
}

void decision_method::set_final_weights(const Eigen::VectorXd &final_weights) {
	final_weights_ = final_weights;
}
