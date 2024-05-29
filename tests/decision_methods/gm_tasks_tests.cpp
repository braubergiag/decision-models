#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../../trunk/core/include/decision_methods/gm_decision_method.h"
#include "../../trunk/core/include/decision_methods/utils.h"

using utils::d;

/*
 * Кривулин Н. К., Абильдаев Т., Горшечникова В. Д., Капаца Д., Магдич Е. А., Мандрикова А. А.
 * О решении многокритериальных задач принятия решений на основе парных сравнений
 * // Компьютерные инструменты в образовании.
 * 2020. № 2. С. 27–58. doi: 10.32603/2071-2340-2020-2-27-58
 * Задача о выборе места работы (стр. 45)
 * */

TEST(GmModule, GmTask_5_1) {
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

TEST(TropicalModule,GmTask_5_2){
	Eigen::MatrixXd A1(4,4),A2(4,4),A3(4,4),A4(4,4),A5(4,4);

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

	Eigen::MatrixXd C(5, 5);
	C << 1,d(1,5),3,d(1,2),5,
			5,1,7,1,7,
			d(1,3),d(1,7),1,d(1,4),3,
			2,1,4,1,7,
			d(1,5),d(1,7),d(1,3),d(1,7),1;

	gm_decision_method gm_model({A1, A2, A3, A4, A5}, C);
	gm_model.perform();

	Eigen::VectorXd actual_final_weights(4);
	actual_final_weights << 0.8505, 0.7429, 1, 0.3232;
	double eps = 0.01;
	ASSERT_NEAR(gm_model.final_weights().norm(), actual_final_weights.norm(), eps);
}