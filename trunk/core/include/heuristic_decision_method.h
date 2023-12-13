//
// Created by igor on 26.12.22.
//

#ifndef TROPICAL_HEURISTIC_DECISION_METHOD_H
#define TROPICAL_HEURISTIC_DECISION_METHOD_H

#include "decision_method.h"
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Core>


class heuristic_decision_method  : public decision_method {

public:
    const std::vector<Eigen::MatrixXd> &get_alternatives() const;
    const Eigen::MatrixXd &get_criteria() const;


    int get_criteria_count() const;
    int get_alternatives_count() const;
    const Eigen::VectorXd &get_final_weights() const;


    void set_criteria(const Eigen::MatrixXd &criteria);
    void set_final_weights(const Eigen::VectorXd &final_weights);

    void set_alternatives(const std::vector<Eigen::MatrixXd> &alternatives);


public:
    heuristic_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const Eigen::MatrixXd &criteria);

private:
    std::vector<Eigen::MatrixXd>  alternatives_;
    Eigen::VectorXd final_weights_;
    Eigen::MatrixXd criteria_;

};


#endif //TROPICAL_HEURISTIC_DECISION_METHOD_H
