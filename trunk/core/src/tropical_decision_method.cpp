
#include "../include/tropical_decision_method.h"
#include "../include/tropical.h"

tropical_decision_method::tropical_decision_method(const vector<MaxAlgMatrixXd> &alternatives,
                                                   const MaxAlgMatrixXd &criteria) : alternatives_(alternatives),
                                                                                     criteria_(criteria) {}

const vector<MaxAlgMatrixXd> &tropical_decision_method::get_alternatives() const {
    return alternatives_;
}

void tropical_decision_method::set_alternatives(const vector<MaxAlgMatrixXd> &alternatives)  {
    alternatives_ = alternatives;
}

const MaxAlgMatrixXd &tropical_decision_method::get_criteria() const {
    return criteria_;
}

void tropical_decision_method::set_criteria(const MaxAlgMatrixXd &criteria)  {
    criteria_ = criteria;
}

void tropical_decision_method::perform()  {
    double lambda = spectral_radius(get_criteria());
    MaxAlgMatrixXd D = construction_generating_matrix_optimal_weights(get_criteria(),lambda);
    int weight_vector_index = get_best_differentiating_weight_vector_index(D);
    MaxAlgMatrixXd v = get_best_differentiating_weight_vector(D, weight_vector_index);
    MaxAlgMatrixXd w = get_worst_differentiating_weight_vector(D);
    MaxAlgMatrixXd P = computing_weighted_sum_pairwise_comparison_matrices(get_alternatives(),v);
    MaxAlgMatrixXd Q = build_generating_matrix_optimal_ratings_alternatives(P);
    MaxAlgMatrixXd x = calc_best_differentiating_vector_ratings_alternatives(D, Q, weight_vector_index);

    MaxAlgMatrixXd R = computing_weighted_sum_pairwise_comparison_matrices(get_alternatives(),w);
    MaxAlgMatrixXd S = build_generating_matrix_optimal_ratings_alternatives(R);
    MaxAlgMatrixXd y = calc_worst_differentiating_vector_ratings_alternatives(S);

    set_final_weights(std::make_pair(x,y));

}
int tropical_decision_method::get_best_differentiating_weight_vector_index(const MaxAlgMatrixXd & D) const{

    MaxAlgVectorXd I(D.rows());
    I.setOnes();
    double current_max = 0;
    int vector_idx = 0;
    for (auto i = 0; i < D.cols(); ++i) {
        MaxAlgMatrixXd x = D.col(i);
        MaxAlgMatrixXd x_ = D.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            vector_idx =  i;
            current_max = r1(0).scalar;
        }

    }
    return vector_idx;

}

MaxAlgMatrixXd tropical_decision_method::get_best_differentiating_weight_vector(const MaxAlgMatrixXd &D, int index) const {
    MaxAlgMatrixXd v = D.col(index) * d(1,static_cast<double>(D.col(index).sum()));
    return v;
}

MaxAlgMatrixXd tropical_decision_method::construction_generating_matrix_optimal_weights(const MaxAlgMatrixXd &
Criteria,double lambda) const{
    MaxAlgMatrixXd D = clini(d(1, lambda) * Criteria);
    return D;
}

MaxAlgMatrixXd tropical_decision_method::get_worst_differentiating_weight_vector(const MaxAlgMatrixXd &D) const{
    MaxAlgVectorXd I(D.rows());
    I.setOnes();

    MaxAlgMatrixXd w = (I.transpose() * D).array().inverse();
    return w;
}

MaxAlgMatrixXd tropical_decision_method::computing_weighted_sum_pairwise_comparison_matrices(std::vector<MaxAlgMatrixXd> alternatives,
                                                                   const MaxAlgMatrixXd &v)const {
    for (auto i = 0; i < v.size(); ++i){
        alternatives[i] *= v(i);
    }
    MaxAlgMatrixXd P(alternatives.at(0).rows(), alternatives.at(0).cols());
    P.setIdentity();

    std::for_each(alternatives.begin(), alternatives.end(),[&P](const auto & alter){
        P += alter;
    });
    return P;
}

MaxAlgMatrixXd tropical_decision_method::build_generating_matrix_optimal_ratings_alternatives(const MaxAlgMatrixXd &P) const {
    double mu = spectral_radius(P);
    MaxAlgMatrixXd Q = clini(d(1, mu) * P);
    return Q;
}

MaxAlgMatrixXd
tropical_decision_method::calc_best_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &D,
                                                                                const MaxAlgMatrixXd &Q, int index) const {
    MaxAlgVectorXd I(D.rows());
    I.setOnes();
    I.resize(Q.rows());
    I.setOnes();
    double current_max = 0;
    int vector_index = 0;
    for (auto i = 0; i < Q.cols(); ++i) {
        MaxAlgMatrixXd x = Q.col(i);
        MaxAlgMatrixXd x_ = Q.array().col(i).inverse();
        auto r1 = ((I.transpose() * x) * (I.transpose() * x_));
        if (current_max < r1(0).scalar) {
            vector_index =  i;
            current_max = r1(0).scalar;
        }

    }
    MaxAlgMatrixXd X = Q.col(vector_index) * d(1, static_cast<double>(Q.col(index).sum()));
    return X;
}

MaxAlgMatrixXd tropical_decision_method::calc_worst_differentiating_vector_ratings_alternatives(const MaxAlgMatrixXd &S) const{
    MaxAlgVectorXd I(S.rows());
    I.setOnes();
    MaxAlgMatrixXd y = (I.transpose() * S).array().inverse().transpose();
    return y;
}

const pair<MaxAlgMatrixXd, MaxAlgMatrixXd> &tropical_decision_method::get_final_weights() const {
    return final_weights_;
}

void tropical_decision_method::set_final_weights(const pair<MaxAlgMatrixXd, MaxAlgMatrixXd> &final_weights) {
    final_weights_ = final_weights;
}
