
#ifndef TROPICAL_TROPICAL_DECISION_METHOD_H
#define TROPICAL_TROPICAL_DECISION_METHOD_H

#include "decision_method.h"
#include "tropical.h"
#include <utility>
class tropical_decision_method : public decision_method{

public:
    tropical_decision_method(const vector<MaxAlgMatrixXd> &alternatives, const MaxAlgMatrixXd &criteria);
    void perform() override;

public:

    const vector<MaxAlgMatrixXd> &get_alternatives() const;
    const MaxAlgMatrixXd &get_criteria() const;

    const pair<MaxAlgMatrixXd, MaxAlgMatrixXd> &get_final_weights() const;



    void set_criteria(const MaxAlgMatrixXd &criteria);
    void set_alternatives(const vector<MaxAlgMatrixXd> &alternatives);


public:

    int get_best_differentiating_weight_vector_index(const MaxAlgMatrixXd & D) const;
    MaxAlgMatrixXd get_best_differentiating_weight_vector(const MaxAlgMatrixXd & D, int index) const;
    MaxAlgMatrixXd get_worst_differentiating_weight_vector(const MaxAlgMatrixXd & D) const;
    MaxAlgMatrixXd construction_generating_matrix_optimal_weights(const MaxAlgMatrixXd & Criteria,double lambda) const;
    MaxAlgMatrixXd computing_weighted_sum_pairwise_comparison_matrices(std::vector<MaxAlgMatrixXd> alternatives ,
                                                                       const MaxAlgMatrixXd &v) const;
    MaxAlgMatrixXd build_generating_matrix_optimal_ratings_alternatives(const MaxAlgMatrixXd &P) const;
    MaxAlgMatrixXd calc_best_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &D,
                                                                         const MaxAlgMatrixXd &Q, int index) const;
    MaxAlgMatrixXd calc_worst_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &S) const;

private:
    void set_final_weights(const pair<MaxAlgMatrixXd, MaxAlgMatrixXd> &final_weights);


private:
    std::vector<MaxAlgMatrixXd>  alternatives_;
    std::pair<MaxAlgMatrixXd,MaxAlgMatrixXd> final_weights_;
    MaxAlgMatrixXd criteria_;
};


#endif //TROPICAL_TROPICAL_DECISION_METHOD_H
