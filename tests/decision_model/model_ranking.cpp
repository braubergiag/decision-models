#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <QString>
#include "../../trunk/core/include/decision_model.h"
#include "../../trunk/core/include/decision_methods/utils.h"


TEST(DecisionMethods, modelRanking) {
	const std::string equality_sign = DecisionModel::equality_sign;
	const std::string greater_sign = DecisionModel::greater_sign;
	const std::string alt_sign = DecisionModel::alternative_sign;

	Eigen::VectorXd weights(3);
	weights << 0.25, 1, 0.4;
	ASSERT_EQ(DecisionModel::modelRanking(weights),
			  alt_sign + "2" + utils::wrap_with_spaces(greater_sign) +
			  alt_sign + "3" + utils::wrap_with_spaces(greater_sign) +
			  alt_sign + "1");


	weights << 1, 0.5, 1;
	ASSERT_EQ(DecisionModel::modelRanking(weights),
			 alt_sign + "1" + utils::wrap_with_spaces(equality_sign) +
			 alt_sign + "3" + utils::wrap_with_spaces(greater_sign) +
			 alt_sign + "2");

	weights << 1, 1, 1;
	ASSERT_EQ(DecisionModel::modelRanking(weights),
			  alt_sign + "1" + utils::wrap_with_spaces(equality_sign) +
			  alt_sign + "2" + utils::wrap_with_spaces(equality_sign) +
			  alt_sign + "3");

	weights << 1, 0.5, 0.5;
	ASSERT_EQ(DecisionModel::modelRanking(weights),
			  alt_sign + "1" + utils::wrap_with_spaces(greater_sign) +
			  alt_sign + "2" + utils::wrap_with_spaces(equality_sign) +
			  alt_sign + "3");
}


TEST(DecisionModel, ParseComparisonValue) {
	using utils::Fraction;
	using utils::d;
	Fraction r(2,4);
	ASSERT_EQ(r.view(), "2/4");
	ASSERT_EQ(r.inv_view(), "4/2");
	ASSERT_DOUBLE_EQ(r.value(), d(2,4));
	ASSERT_DOUBLE_EQ(r.inv_value(), d(4,2));

	Fraction r2(1,4);
	ASSERT_EQ(r2.view(), "1/4");
	ASSERT_EQ(r2.inv_view(), "4");
	ASSERT_DOUBLE_EQ(r2.value(), d(1,4));
	ASSERT_DOUBLE_EQ(r2.inv_value(), d(4,1));
}