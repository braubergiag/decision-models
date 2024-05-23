#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../trunk/core/include/decision_methods/gm_decision_method.h"

inline double d(double p, double q) {
    return p / q;
}

TEST(GmModule, Task_5_1) {
    //5.1. Решение задачи о выборе места работы"
    Eigen::MatrixXd A1(3, 3), A2(3, 3), A3(3, 3), A4(3, 3), A5(3, 3), A6(3, 3);

    A1 << 1, d(1, 4), d(1, 2),
            4, 1, 3,
            2, d(1, 3), 1;
    A2 << 1, d(1, 4), d(1, 5),
            4, 1, d(1, 2),
            5, 2, 1;
    A3 << 1, 3, d(1, 3),
            d(1, 3), 1, 1,
            3, 1, 1;
    A4 << 1, d(1, 3), 5,
            3, 1, 7,
            d(1, 5), d(1, 7), 1;
    A5 << 1, 1, 7,
            1, 1, 7,
            d(1, 7), d(1, 7), 1;
    A6 << 1, 7, 9,
            d(1, 7), 1, 5,
            d(1, 9), d(1, 5), 1;


	Eigen::MatrixXd C(6, 6);
    C << 1, 1, 1, 4, 1, d(1, 2),
            1, 1, 2, 4, 1, d(1, 2),
            1, d(1, 2), 1, 5, 3, d(1, 2),
            d(1, 4), d(1, 4), d(1, 5), 1, d(1, 3), d(1, 3),
            1, 1, d(1, 3), 3, 1, 1,
            2, 2, 2, 3, 1, 1;


    gm_decision_method gm_model({A1, A2, A3, A4, A5, A6}, C);
    gm_model.perform();


    Eigen::MatrixXd final_weights(1, 3);
    final_weights << 0.9212, 1, 0.5373;

    double eps = 0.01;
    ASSERT_NEAR(gm_model.final_weights().norm(), final_weights.norm(), eps);
}