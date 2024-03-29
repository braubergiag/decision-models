#include "../include/ahp_decision_method.h"
#include <Eigen/Eigenvalues>
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::EigenSolver;


ahp_decision_method::ahp_decision_method(const std::vector<Eigen::MatrixXd> &alternatives, const MatrixXd &criteria)
        : heuristic_decision_method(alternatives, criteria) {}

Eigen::MatrixXcd ahp_decision_method::main_eigenvector(const MatrixXd &matrix) const {
    EigenSolver<MatrixXd> eigen_solver(matrix);
    Eigen::VectorXcd eigen_vector = eigen_solver.eigenvectors().col(0).real();
    double sum = eigen_vector.cwiseAbs().sum();
    std::transform(eigen_vector.begin(),eigen_vector.end(),eigen_vector.begin(),
                   [sum](auto & el){
        return abs(el) / sum;
    });
    return eigen_vector.real();
}


Eigen::MatrixXd
ahp_decision_method::weight_matrix(const std::vector<Eigen::MatrixXcd> &alternatives_main_eigen_vectors) const {

    Eigen::MatrixXd weights(alternatives_count(), criteria_count());
    for (int i = 0; i < criteria_count(); ++i){
        for (int j = 0; j < alternatives_count(); ++j) {
            weights(j,i) = alternatives_main_eigen_vectors.at(i).coeff(j).real();
        }

    }

    return weights;
}

Eigen::VectorXd ahp_decision_method::weight_vector(const Eigen::VectorXcd &criteria_main_eigen_vector,
                                                   const std::vector<Eigen::MatrixXcd> &alternatives_main_eigen_vectors) const {
    return (weight_matrix(alternatives_main_eigen_vectors) * criteria_main_eigen_vector).real();
}

void ahp_decision_method::perform()  {

    Eigen::VectorXcd criteria_main_eigen_vector = main_eigenvector(criteria());
    std::vector<Eigen::MatrixXcd> alternatives_main_eigen_vectors;
    std::transform(alternatives().begin(),
                   alternatives().end(),
                   std::back_inserter(alternatives_main_eigen_vectors),
                   [this](const auto & alter_matrix){
                       return main_eigenvector(alter_matrix);
                   });

    set_final_weights(weight_vector(criteria_main_eigen_vector, alternatives_main_eigen_vectors));



}
