#pragma once

#include <vector>
#include <algorithm>
#include <Eigen/Dense>

using namespace Eigen;

template<typename T>
struct MaxAlg {
	T scalar;
	MaxAlg() = default;
	MaxAlg(T scalar) noexcept : scalar(scalar) {}
	operator T() const noexcept { return scalar; }

	MaxAlg &operator+=(MaxAlg right) noexcept {
		scalar = std::max(scalar, right.scalar);
		return *this;
	}

	friend MaxAlg operator+(MaxAlg left, MaxAlg right) noexcept {
		left += right;
		return left;
	}

	MaxAlg &operator*=(MaxAlg right) noexcept {
		scalar *= right.scalar;
		return *this;
	}

	MaxAlg &operator/=(MaxAlg right) noexcept {
		scalar /= right.scalar;
		return *this;
	}

	friend MaxAlg operator-=(MaxAlg left, MaxAlg right) noexcept {
		return left;
	}

	friend MaxAlg operator*(MaxAlg left, MaxAlg right) noexcept {
		left *= right;
		return left;
	}

	friend MaxAlg operator-(MaxAlg left, MaxAlg right) noexcept {
		return left;
	}

	friend MaxAlg operator/(MaxAlg left, MaxAlg right) noexcept {
		left /= right;
		return left;
	}
};


template<class T>
double sqrt(const MaxAlg<T> &val) {
	return ::sqrt(val.scalar);
}


template<class T, Eigen::Index Rows, Eigen::Index Cols>
using MaxAlgMatrix = Eigen::Matrix<MaxAlg<T>, Rows, Cols>;

template<class T, Eigen::Index Rows, Eigen::Index Cols>
using MaxAlgArray = Eigen::Array<MaxAlg<T>, Rows, Cols>;
