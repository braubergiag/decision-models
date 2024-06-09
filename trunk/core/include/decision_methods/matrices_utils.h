#pragma once

#include <Eigen/Core>

namespace matrices_utils {
	template<typename T>
	Eigen::MatrixX<T> removeRow(const Eigen::MatrixX<T> &matrix, int index);
	template<typename T>
	Eigen::MatrixX<T> removeColumn(const Eigen::MatrixX<T> &matrix, int index);

	template<typename T>
	Eigen::MatrixX<T> removeRowAndColumn(const Eigen::MatrixX<T> &matrix, int rowIndex, int columnIndex);

	template<typename T>
	Eigen::MatrixX<T> addRow(const Eigen::MatrixX<T> &matrix, T rowValue);

	template<typename T>
	Eigen::MatrixX<T> addColumn(const Eigen::MatrixX<T> &matrix, T columnValue);

	template<typename T>
	Eigen::MatrixX<T> addRowAndColumn(const Eigen::MatrixX<T> &matrix, T rowValue, T columnValue);
} // namespace matrices_utils

namespace matrices_utils {
	template<typename T>
	Eigen::MatrixX<T> removeColumn(const Eigen::MatrixX<T> &matrix, int index) {
		if (index > (matrix.cols() - 1))
			return matrix;
		if (matrix.cols() == 1) {
			return Eigen::MatrixX<T>();
		}
		auto new_rows_count = matrix.rows();
		auto new_cols_count = matrix.cols() - 1;

		Eigen::MatrixX<T> result(new_rows_count, new_cols_count);
		result.leftCols(index) = matrix.leftCols(index);
		result.rightCols(matrix.cols() - index - 1) = matrix.rightCols(matrix.cols() - index - 1);
		return result;
	}

	template<typename T>
	Eigen::MatrixX<T> removeRow(const Eigen::MatrixX<T> &matrix, int index) {
		if (index > (matrix.rows() - 1))
			return matrix;
		if (matrix.rows() == 1) {
			return Eigen::MatrixX<T>();
		}
		auto new_rows_count = matrix.rows() - 1;
		auto new_cols_count = matrix.cols();

		Eigen::MatrixX<T> result(new_rows_count, new_cols_count);
		result.topRows(index) = matrix.topRows(index);
		result.bottomRows(matrix.rows() - index - 1) = matrix.bottomRows(matrix.rows() - index - 1);
		return result;
	}

	template<typename T>
	Eigen::MatrixX<T> removeRowAndColumn(const Eigen::MatrixX<T> &matrix, int rowIndex, int columnIndex) {
		Eigen::MatrixX<T> result(matrix);
		result = removeRow(result, rowIndex);
		result = removeColumn(result, columnIndex);
		return result;
	}

	template<typename T>
	Eigen::MatrixX<T> addRow(const Eigen::MatrixX<T> &matrix, T rowValue) {
		Eigen::MatrixX<T> result(matrix);
		if (result.size() == 0)
			return Eigen::MatrixX<T>::Constant(1, 1, rowValue);
		result.conservativeResize(result.rows() + 1, result.cols());
		result.row(result.rows() - 1) = Eigen::VectorX<T>::Constant(result.cols(), rowValue);
		return result;
	}

	template<typename T>
	Eigen::MatrixX<T> addColumn(const Eigen::MatrixX<T> &matrix, T columnValue) {
		Eigen::MatrixX<T> result(matrix);
		if (result.size() == 0)
			return Eigen::MatrixX<T>::Constant(1, 1, columnValue);
		result.conservativeResize(result.rows(), result.cols() + 1);
		result.col(result.cols() - 1) = Eigen::VectorX<T>::Constant(result.rows(), columnValue);
		return result;
	}

	template<typename T>
	Eigen::MatrixX<T> addRowAndColumn(const Eigen::MatrixX<T> &matrix, T rowValue, T columnValue) {
		Eigen::MatrixX<T> result(matrix);
		if (result.size() == 0)
			return Eigen::MatrixX<T>::Constant(1, 1, rowValue);
		result = addRow(result, rowValue);
		result = addColumn(result, columnValue);
		return result;
	}

} // namespace matrices_utils