#pragma once

#include <iostream>
#include <string>
#include <Eigen/Core>

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

	friend MaxAlg operator*(MaxAlg left, MaxAlg right) noexcept {
		left *= right;
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

inline double d(double p, double q) {
	return p / q;
}

template<class T, Eigen::Index Rows, Eigen::Index Cols>
using MaxAlgMatrix = Eigen::Matrix<MaxAlg<T>, Rows, Cols>;

template<class T, Eigen::Index Rows, Eigen::Index Cols>
using MaxAlgArray = Eigen::Array<MaxAlg<T>, Rows, Cols>;


using MaxAlgMatrixXd = MaxAlgMatrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using MaxAlgVectorXd = MaxAlgMatrix<double, Eigen::Dynamic, 1>;
using MaxAlgArrayXXd = MaxAlgArray<double, Eigen::Dynamic, Eigen::Dynamic>;
using MaxAlgArrayXd = MaxAlgArray<double, Eigen::Dynamic, 1>;


std::ostream &operator<<(std::ostream &stream, const MaxAlgMatrixXd &matrixXd);
bool operator>=(const MaxAlgVectorXd &lhs, const MaxAlgVectorXd &rhs);

MaxAlgMatrixXd kleene_star(const MaxAlgMatrixXd &mat);
double spectral_radius(const MaxAlgMatrixXd &mat);

std::pair<bool, int> find_dominating_vector(const std::vector<MaxAlgVectorXd> &v);
void remove_dominating_vectors(std::vector<MaxAlgVectorXd> &v);
