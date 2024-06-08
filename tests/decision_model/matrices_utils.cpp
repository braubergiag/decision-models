#include <gtest/gtest.h>
#include <matrices_utils.h>
using namespace matrices_utils;

TEST(MatricesUtilsTests, RemoveRowAndColumn) {
	Eigen::MatrixXd matrix(3, 3);
	matrix << 	1, 2, 3,
				4, 5, 6,
				7, 8, 9;

	Eigen::MatrixXd expected(2, 2);
	expected << 1, 3,
				7, 9;

	auto result = removeRowAndColumn(matrix, 1, 1);
	ASSERT_TRUE(result.isApprox(expected));
}

TEST(MatricesUtilsTests, RemoveRowAndColumnIncorrectIndex) {
	Eigen::MatrixXd matrix(3, 3);
	matrix << 	1, 2, 3,
				4, 5, 6,
				7, 8, 9;

	Eigen::MatrixXd expected(3, 3);
	expected << 1, 2, 3,
				4, 5, 6,
				7, 8, 9;

	auto result = removeRowAndColumn(matrix, 3, 3);
	ASSERT_TRUE(result.isApprox(expected));
}

TEST(MatricesUtilsTests, RemoveRowLowDim) {
	Eigen::MatrixXd matrix(1, 3);
	matrix << 	1, 2, 3;

	Eigen::MatrixXd expected(1, 3);
	expected << 1, 2, 3;

	auto result = removeRow(matrix, 1);
	ASSERT_TRUE(result.isApprox(expected));
}

TEST(MatricesUtilsTests, RemoveColLowDim) {
	Eigen::MatrixXd matrix(3, 1);
	matrix << 	1,
				2,
				3;

	Eigen::MatrixXd expected(3, 1);
	expected << 1,
				2,
				3;

	auto result = removeColumn(matrix, 1);
	ASSERT_TRUE(result.isApprox(expected));
}

TEST(MatricesUtilsTests,AddRowAndColumn) {
	Eigen::MatrixXd matrix(3, 3);
	matrix << 	1, 2, 3,
				4, 5, 6,
				7, 8, 9;

	Eigen::MatrixXd expected(4, 4);
	expected << 1,2,3,1,
				4,5,6,1,
				7,8,9,1,
				1,1,1,1;

	auto result = addRowAndColumn(matrix, 1., 1.);
	ASSERT_TRUE(result.isApprox(expected));
}
