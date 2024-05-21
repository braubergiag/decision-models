#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../trunk/core/include/ahp_decision_method.h"

inline double d(double p, double q) {
    return p / q;
}

using Eigen::VectorXd;
using Eigen::MatrixXcd;
TEST(AHPModule,AHP_Task_1) {
	Eigen::MatrixXd A1(3,3),A2(3,3),A3(3,3),A4(3,3),A5(3,3),A6(3,3);

    A1 <<   1,d(1,3),d(1,2),
             3,1,3,
             2,d(1,3),1;
    A2 <<   1,1,1,
            1,1,1,
            1,1,1;
    A3 <<   1,5,1,
            d(1,5),1,d(1,5),
            1,5,1;
    A4 <<   1,9,7,
            d(1,9),1,d(1,5),
            d(1,7),5,1;
    A5 <<   1,d(1,2),1,
            2,1,2,
            1,d(1,2),1;
    A6 <<   1,6,4,
            d(1,6),1,d(1,3),
            d(1,4),3,1;

	Eigen::MatrixXd C(6,6);
    C << 1,4,3,1,3,4,
        d(1,4),1,7,3,d(1,5),1,
        d(1,3),d(1,7),1,d(1,5),d(1,5),d(1,6),
        1,d(1,3),5,1,1,d(1,3),
        d(1,3),5,5,1,1,3,
        d(1,4),1,6,3,d(1,3),1;


    ahp_decision_method ahp_model({A1,A2,A3,A4,A5,A6},C);
    double eps = 0.01;
    Eigen::MatrixXcd main_eigen_vector = ahp_model.main_eigenvector(C).col(0).real();
    Eigen::MatrixXcd actual_main_eigen_vector(1,6);
    actual_main_eigen_vector << 0.32, 0.14, 0.03, 0.13, 0.24, 0.14;
    ASSERT_NEAR(actual_main_eigen_vector.norm(),main_eigen_vector.norm(),eps);


    Eigen::MatrixXd final_weights_actual(1,3);
    final_weights_actual <<  0.43211 , 0.342146 ,0.225744 ;
    ahp_model.perform();
    VectorXd final_weights =  ahp_model.final_weights();
    ASSERT_NEAR( final_weights.norm(), final_weights_actual.norm(), eps);
}

TEST(AHPModule, AHP_Task_5_1) {

    //5.1. Решение задачи о выборе места работы"
	Eigen::MatrixXd A1(3,3),A2(3,3),A3(3,3),A4(3,3),A5(3,3),A6(3,3);

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


	Eigen::MatrixXd C(6, 6);
    C << 1, 1,1,4,1,d(1,2),
            1,1,2,4,1,d(1,2),
            1,d(1,2),1,5,3,d(1,2),
            d(1,4),d(1,4),d(1,5),1,d(1,3),d(1,3),
            1,1,d(1,3),3,1,1,
            2,2,2,3,1,1;


    ahp_decision_method ahp_model({A1,A2,A3,A4,A5,A6},C);
    ahp_model.perform();

    Eigen::MatrixXd actual_final_weights(1, 3);
    actual_final_weights << 0.3843 ,0.3516 ,0.2641;

    double eps = 0.01;
    ASSERT_NEAR(ahp_model.final_weights().norm(), actual_final_weights.norm(), eps);
}