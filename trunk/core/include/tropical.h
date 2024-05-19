#pragma once

#include "max_algebra.h"
#include <iostream>
#include <string>

using MaxAlgMatrixXd = MaxAlgMatrix<double, Eigen::Dynamic, Eigen::Dynamic>;
using MaxAlgVectorXd = MaxAlgMatrix<double, Eigen::Dynamic, 1>;
using MaxAlgArrayXXd = MaxAlgArray<double, Eigen::Dynamic, Eigen::Dynamic>;
using MaxAlgArrayXd = MaxAlgArray<double, Eigen::Dynamic, 1>;

template<typename T>
void PrintLog(const T &t, std::string hint = {}, std::string delim = "\n") {
	std::cout << hint << delim;
	std::cout << t << std::endl;
}
std::ostream &operator<<(std::ostream &stream, const MaxAlgMatrixXd &matrixXd);
MaxAlgMatrixXd clini(const MaxAlgMatrixXd &matrixXd);
double spectral_radius(const MaxAlgMatrixXd &matrixXd);


inline double d(double p, double q) {
	return p / q;
}
