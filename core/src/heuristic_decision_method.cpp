//
// Created by igor on 26.12.22.
//

#include "../include/heuristic_decision_method.h"

heuristic_decision_method::heuristic_decision_method(const std::vector<Eigen::MatrixXd> &alternatives,
                                                     const Eigen::MatrixXd &criteria) : alternatives_(alternatives),
                                                                                        criteria_(criteria) {}

const std::vector<Eigen::MatrixXd> &heuristic_decision_method::get_alternatives() const {
    return alternatives_;
}

void heuristic_decision_method::set_alternatives(const std::vector<Eigen::MatrixXd> &alternatives) {
    alternatives_ = alternatives;
}

const Eigen::MatrixXd &heuristic_decision_method::get_criteria() const {
    return criteria_;
}

void heuristic_decision_method::set_criteria(const Eigen::MatrixXd &criteria) {
    criteria_ = criteria;
}

int heuristic_decision_method::get_criteria_count() const {
    return alternatives_.size();
}

int heuristic_decision_method::get_alternatives_count() const {
    return alternatives_.at(0).rows();
}

const Eigen::VectorXd &heuristic_decision_method::get_final_weights() const {
    return final_weights_;
}

void heuristic_decision_method::set_final_weights(const Eigen::VectorXd &final_weights) {
    final_weights_ = final_weights;
}
