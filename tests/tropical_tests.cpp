#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../trunk/core/include/tropical.h"
using MaxAlgMatrixXd = MaxAlgMatrix<double ,Eigen::Dynamic,Eigen::Dynamic>;
using MaxAlgVectorXd = MaxAlgMatrix<double, Eigen::Dynamic,1>;
using MaxAlgArrayXXd = MaxAlgArray<double , Eigen::Dynamic, Eigen::Dynamic>;
using MaxAlgArrayXd = MaxAlgArray<double, Eigen::Dynamic,1>;

TEST(TropicalModule, spectral_radius){
    MaxAlgMatrixXd A1(4,4);
    const double epsilon = 0.001;

    A1 << 1,3,4,2,
         d(1,3),1,d(1,2),d(1,3),
         d(1,4),2,1,4,
         d(1,2),3,d(1,4),1;
    ASSERT_NEAR(spectral_radius(A1), 2.0, epsilon);


    MaxAlgMatrixXd A2(4,4);
    A2 << 1,d(1,3),d(1,2),d(1,3),
        3,1,4,1,
        2,d(1,4),1,2,
        3,1,d(1,2),1;
    ASSERT_NEAR(spectral_radius(A2), 2.0, epsilon);

}

TEST(TropicalModule, clini){

    MaxAlgMatrixXd  A1(4,4), A_clini(4,4);
    const double epsilon = 0.001;
    A1 << d(1,2), d(3,2), 2, 1,
        d(1,6),d(1,2),d(1,4),d(1,6),
        d(1,8),1,d(1,2),2,
        d(1,4),d(3,2),d(1,8),d(1,2);

    A_clini <<  1,6,2,4,
                d(1,6),1,d(1,3),d(2,3),
                d(1,2),3,1,2,
                d(1,4),d(3,2),d(1,2),1;

    ASSERT_NEAR(clini(A1).norm().scalar, A_clini.norm().scalar,epsilon);

    MaxAlgMatrixXd A2(4,4);
    A2 << d(1,2), d(1,6),d(1,4),d(1,6),
        d(3,2),d(1,2),2,d(1,2),
        1,d(1,8),d(1,2),1,
        d(3,2),d(1,2),d(1,4),d(1,2);

    MaxAlgMatrixXd A2_clini(4,4);
    A2_clini << 1,d(1,6),d(1,3),d(1,3),
                3,1,2,2,
                d(3,2),d(1,2),1,1,
                d(3,2),d(1,2),1,1;
    ASSERT_NEAR(clini(A2).norm().scalar, A2_clini.norm().scalar,epsilon);
}


TEST(TropicalModule,Trace){
    MaxAlgMatrixXd A1(3,3),A2(3,3),A3(3,3),A4(3,3),A5(3,3),A6(3,3);

    A1 <<   1,2,3,
            4,5,3,
            2,4,2;
    ASSERT_EQ(A1.trace(), 5.0);


    A2 <<   d(1,2), 1,      1,
            1,      d(1,4), 1,
            1,      2,      d(1,5);
    ASSERT_EQ(A2.trace(), 0.5);

    A3 <<   100,1,  1,
            0,  10, 1,
            3,  1,  1;
    ASSERT_EQ(A3.trace(), 100.0);

}