#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../../trunk/core/include/decision_methods/ahp_decision_method.h"
#include "../../trunk/core/include/decision_methods/utils.h"

using utils::d;

/*
 * Кривулин Н. К., Абильдаев Т., Горшечникова В. Д., Капаца Д., Магдич Е. А., Мандрикова А. А.
 * О решении многокритериальных задач принятия решений на основе парных сравнений
 * // Компьютерные инструменты в образовании.
 * 2020. № 2. С. 27–58. doi: 10.32603/2071-2340-2020-2-27-58
 * Задача о выборе места работы (стр. 45)
 * */


TEST(AHPModule, AHPTask_5_1) {
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


	ahp_decision_method ahp_model({A1, A2, A3, A4, A5, A6}, C);
	ahp_model.perform();

	Eigen::VectorXd actual_final_weights(3);
	actual_final_weights << 1, 0.9151, 0.6872;
	double eps = 0.1;
	ASSERT_TRUE(ahp_model.final_weights().isApprox(actual_final_weights, eps));
}