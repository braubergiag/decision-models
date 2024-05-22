#include <gtest/gtest.h>
#include "../trunk/core/include/decision_methods/tropical.h"
#include "../trunk/core/include/decision_methods/tropical_decision_method.h"

TEST(TropicalModule,TropicalTask_5_1) {
        //5.1. Решение задачи о выборе места работы"
        MaxAlgMatrixXd A1(3,3),A2(3,3),A3(3,3),A4(3,3),A5(3,3),A6(3,3);

        A1 << 1,d(1,4),d(1,2),
                4,1,3,
                2,d(1,3),1;
        A2 << 1,d(1,4),d(1,5),
                4,1,d(1,2),
                5,2,1;
        A3 << 1,3,d(1,3),
                d(1,3),1,1,
                3,1,1;
        A4 << 1,d(1,3),5,
                3,1,7,
                d(1,5),d(1,7),1;
        A5 << 1,1,7,
                1,1,7,
                d(1,7),d(1,7),1;
        A6 << 1,7,9,
                d(1,7),1,5,
                d(1,9),d(1,5),1;


        MaxAlgMatrixXd C(6, 6);
        C << 1, 1,1,4,1,d(1,2),
                1,1,2,4,1,d(1,2),
                1,d(1,2),1,5,3,d(1,2),
                d(1,4),d(1,4),d(1,5),1,d(1,3),d(1,3),
                1,1,d(1,3),3,1,1,
                2,2,2,3,1,1;

    const double epsilon = 0.001;
    double lambda = spectral_radius(C);
    double lambda_actual = 1.8612;
    ASSERT_NEAR(lambda,lambda_actual,epsilon);
    tropical_decision_method method({A1,A2,A3,A4,A5,A6},C);
    MaxAlgMatrixXd D = method.optimal_weights_matrix(C, lambda);
    MaxAlgMatrixXd D_calc(D.rows(),D.cols());
    D_calc <<
            1,              0.537285,   0.57735 ,   2.14914 ,   0.930605,   0.5,
            1,              1,          1.07457,    2.88675,    1.73205,    0.930605,
            0.930605,       0.930605,   1,          2.68642,    1.61185,    0.866025,
            0.19245,        0.19245,    0.206801,   1,          0.333333,   0.179095,
            0.57735,        0.57735,    0.620403,   1.66667,    1,          0.537285,
            1.07457,        1.07457,    1.1547,     3.10202,    1.86121,    1;

    ASSERT_NEAR(D.norm().scalar,D_calc.norm().scalar, epsilon);


    std::vector<int> vector_indices = method.best_diff_weight_vector_indices(D);
    auto l_ = vector_indices.front();
	int l_actual = 0;
    ASSERT_EQ(l_,l_actual);


	std::vector<MaxAlgVectorXd> best_weight_vectors = method.best_diff_weight_vectors(D, vector_indices);
	auto v = best_weight_vectors.front();
    MaxAlgMatrixXd v_actual(v.rows(),v.cols());
    v_actual << 0.930605,0.930605,0.866025,0.179095,0.537285,1;

    ASSERT_NEAR(v.norm().scalar, v_actual.norm().scalar,epsilon);

    MaxAlgMatrixXd w = method.worst_diff_weight_vector(D);
    MaxAlgMatrixXd w_actual(w.rows(),w.cols());
    w_actual << 0.930605, 0.930605, 0.866025, 0.322371, 0.537285 ,1;
    ASSERT_NEAR(w.norm().scalar, w_actual.norm().scalar,epsilon);


    // 2.1
    std::vector<MaxAlgMatrixXd> Alternatives {A1,A2,A3,A4,A5,A6};
    MaxAlgMatrixXd P = method.weighted_sum_pairwise_comparison_matrices(Alternatives, v);
    MaxAlgMatrixXd P_actual(P.rows(),P.cols());
    P_actual << 1,         7,       9,
                3.72242,   1,       5,
                4.65302,   1.86121, 1;
    ASSERT_NEAR(P.norm().scalar, P_actual.norm().scalar,epsilon);


    // 2.2
    MaxAlgMatrixXd Q = method.build_alternatives_ratings_matrix(P);
    MaxAlgMatrixXd Q_actual(Q.rows(),Q.cols());
    Q_actual <<         1,          1.08171,    1.39076,
                        0.575223,   1,          0.8,
                        0.719029,   0.777778,   1;
    ASSERT_NEAR(Q.norm().scalar, Q_actual.norm().scalar,epsilon);


    // 2.3
	std::vector<MaxAlgVectorXd> best_diff_alter_vectors = method.best_diff_alternatives_ratings_vectors(Q);
	auto X = best_diff_alter_vectors.front();
    MaxAlgMatrixXd X_actual(X.rows(),X.cols());
    X_actual << 1, 0.575223, 0.719029;
    ASSERT_NEAR(X.norm().scalar, X_actual.norm().scalar,epsilon);

    // 3
    // 3.1
    MaxAlgMatrixXd R = method.weighted_sum_pairwise_comparison_matrices(Alternatives, w);
    MaxAlgMatrixXd R_actual(R.rows(),R.cols());
    R_actual <<     1,              7,         9,
                    3.72242,        1,         5,
                    4.65302,        1.86121,   1;
    ASSERT_NEAR(R.norm().scalar, R_actual.norm().scalar,epsilon);


    // 3.2
    MaxAlgMatrixXd S = method.build_alternatives_ratings_matrix(R);
    MaxAlgMatrixXd S_actual(S.rows(), S.cols());
    S_actual <<     1,          1.08171,    1.39076,
                    0.575223,   1,          0.8,
                    0.719029,   0.777778,   1;
    ASSERT_NEAR(S.norm().scalar, S_actual.norm().scalar,epsilon);


    // 3.3
    MaxAlgMatrixXd y = method.worst_diff_alternatives_ratings_vector(S);
    MaxAlgMatrixXd y_actual(y.rows(),y.cols());
    y_actual << 1,  0.924466,   0.719029;
    ASSERT_NEAR(y.norm().scalar, y_actual.norm().scalar,epsilon);
}

TEST(TropicalModule,TropicalTask_5_2){
    //  Решение задачи 5.2
    MaxAlgMatrixXd A1(4,4),A2(4,4),A3(4,4),A4(4,4),A5(4,4);
    A1 << 1,d(1,2),1,d(1,2),
            2,1,d(5,2),1,
            1,d(2,5),1,d(2,5),
            2,1,d(5,2),1;
    A2 << 1,2,d(1,3),4,
            d(1,2),1,d(1,8),2,
            3,8,1,9,
            d(1,4),d(1,2),d(1,9),1;
    A3 << 1,5,d(1,2),d(5,2),
            d(1,5),1,d(1,9),d(1,4),
            2,9,1,7,
            d(2,5),4,d(1,7),1;
    A4 << 1,d(1,2),3,4,
            2,1,6,8,
            d(1,3),d(1,6),1,1,
            d(1,4),d(1,8),1,1;
    A5 << 1,d(3,2),d(1,2),4,
            d(2,3),1,d(2,7),d(5,2),
            2,d(7,2),1,9,
            d(1,4),d(2,5),d(1,9),1;

    MaxAlgMatrixXd C(5, 5);
    C << 1,d(1,5),3,d(1,2),5,
            5,1,7,1,7,
            d(1,3),d(1,7),1,d(1,4),3,
            2,1,4,1,7,
            d(1,5),d(1,7),d(1,3),d(1,7),1;



    const double epsilon = 0.001;
    double lambda = spectral_radius(C);
    double lambda_actual = 1.59231;
    ASSERT_NEAR(lambda,lambda_actual,epsilon);
    tropical_decision_method method({A1,A2,A3,A4,A5},C);
    MaxAlgMatrixXd D = method.optimal_weights_matrix(C, lambda);
    MaxAlgMatrixXd D_calc(D.rows(),D.cols());
    D_calc <<
           1,  0.318463,   1.88405,  0.318463,   3.54965,
    3.14008,         1,   5.91608,         1,   11.1462,
    0.530771,  0.169031,         1,  0.169031,   1.88405,
    1.97203,  0.628017,    3.7154,         1,         7,
    0.281718, 0.0897167,  0.530771, 0.0897167,         1;

    ASSERT_NEAR(D.norm().scalar,D_calc.norm().scalar, epsilon);


	std::vector<int> vector_indices = method.best_diff_weight_vector_indices(D);
	auto l_ = vector_indices.front();
    int l_actual = 0;
    ASSERT_EQ(l_,l_actual);


    std::vector<MaxAlgVectorXd> best_weight_vectors = method.best_diff_weight_vectors(D, vector_indices);
	auto v = best_weight_vectors.front();
    MaxAlgVectorXd v_actual(v.rows(),v.cols());
    v_actual <<  0.318463,1, 0.169031 , 0.628017, 0.0897167;

    ASSERT_NEAR(v.norm().scalar, v_actual.norm().scalar,epsilon);

    MaxAlgMatrixXd w = method.worst_diff_weight_vector(D);
    MaxAlgMatrixXd w_actual(w.rows(),w.cols());
    w_actual << 0.318463,         1,  0.169031,         1, 0.0897167;
    ASSERT_NEAR(w.norm().scalar, w_actual.norm().scalar,epsilon);


    // 2.1
    std::vector<MaxAlgMatrixXd> Alternatives {A1,A2,A3,A4,A5};
    MaxAlgMatrixXd P = method.weighted_sum_pairwise_comparison_matrices(Alternatives, v);
    MaxAlgMatrixXd P_actual(P.rows(),P.cols());
    P_actual << 1,        2,        1.88405 ,        4,
                1.25603,  1,        3.7681,          5.02414,
                3,        8,        1 ,              9,
                0.636925, 0.676123, 0.796157,        1;
    ASSERT_NEAR(P.norm().scalar, P_actual.norm().scalar,epsilon);


    // 2.2
    MaxAlgMatrixXd Q = method.build_alternatives_ratings_matrix(P);
    MaxAlgMatrixXd Q_actual(Q.rows(),Q.cols());
    Q_actual << 1,          0.5,        0.343152,       0.72854,
                0.375,      1,          0.686304,       1.125,
                0.546405,   1.45708,    1,              1.63922,
                0.116006,   0.211289,   0.145008,        1;
    ASSERT_NEAR(Q.norm().scalar, Q_actual.norm().scalar,epsilon);


    // 2.3
    std::vector<MaxAlgVectorXd> best_diff_alter_vectors = method.best_diff_alternatives_ratings_vectors(Q);
    auto X = best_diff_alter_vectors.front();

	MaxAlgVectorXd X_actual(X.rows(),X.cols());
    X_actual << 1, 0.375,   0.546405,   0.116006;
    ASSERT_NEAR(X.norm().scalar, X_actual.norm().scalar,epsilon);

    // 3
    // 3.1
    MaxAlgMatrixXd R = method.weighted_sum_pairwise_comparison_matrices(Alternatives, w);
    MaxAlgMatrixXd R_actual(R.rows(),R.cols());
    R_actual <<         1,        2,                3,        4,
                        2,        1,                6,        8,
                        3,        8,                1,        9,
                        0.636925, 0.676123,         1,        1;
    ASSERT_NEAR(R.norm().scalar, R_actual.norm().scalar,epsilon);


    // 3.2
    MaxAlgMatrixXd S = method.build_alternatives_ratings_matrix(R);
    MaxAlgMatrixXd S_actual(S.rows(), S.cols());
    S_actual <<             1,          0.5,        0.433013,   0.57735,
                            0.375,      1,          0.866025,    1.1547,
                            0.433013,   1.1547,     1,          1.33333,
                            0.0919323,  0.166667,   0.144338,         1;
    ASSERT_NEAR(S.norm().scalar, S_actual.norm().scalar,epsilon);


    // 3.3
    MaxAlgMatrixXd y = method.worst_diff_alternatives_ratings_vector(S);
    MaxAlgMatrixXd y_actual(y.rows(),y.cols());
    y_actual <<        1,   0.866025,  1,   0.75;
    ASSERT_NEAR(y.norm().scalar, y_actual.norm().scalar,epsilon);
}
TEST(TropicalModule,SchoolProblem) {
    MaxAlgMatrixXd A1(3,3),A2(3,3),A3(3,3),A4(3,3),A5(3,3), A6(3,3);

    A1 << 1, d(1,3), d(1,2),
        3,1,3,
        2,d(1,3),1;

    A2 << 1, 1, 1,
            1,1,1,
            1,1,1;

    A3 << 1, 5, 1,
            d(1,5),1,d(1,5),
            1,5,1;

    A4 << 1,9,7,
        d(1,9),1,d(1,5),
        d(1,7),5,1;
    A5 << 1,d(1,2),1,
          2,1,2,
          1,d(1,2),1;
    A6 << 1,6,4,
        d(1,6),1,d(1,3),
        d(1,4),3,1;

    MaxAlgMatrixXd C(6, 6);
    C <<    1,5,7,5,3,1,
            d(1,5),1,3,d(1,5),d(1,6),d(1,6),
            d(1,7),d(1,3),1,d(1,4),d(1,5),d(1,5),
            d(1,5),5,4,1,d(1,5),d(1,6),
            d(1,3),6,5,5,1,1,
            1,6,5,6,1,1;

    tropical_decision_method method({A1,A2,A3,A4,A5,A6},C);
    method.perform();
	auto [best_weight, worst_weight] = method.final_weights();
}