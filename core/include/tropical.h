
#ifndef TROPICAL_TROPICAL_H
#define TROPICAL_TROPICAL_H

#include "max_algebra.h"
#include <iostream>
#include <string>

using MaxAlgMatrixXd = MaxAlgMatrix<double ,Eigen::Dynamic,Eigen::Dynamic>;
using MaxAlgVectorXd = MaxAlgMatrix<double, Eigen::Dynamic,1>;
using MaxAlgArrayXXd = MaxAlgArray<double , Eigen::Dynamic, Eigen::Dynamic>;
using MaxAlgArrayXd = MaxAlgArray<double, Eigen::Dynamic,1>;

template <typename T>
void PrintLog(const T& t, string hint = {},string delim = "\n") {
    std::cout << hint << delim;
    std::cout << t << std::endl;
}
double Tr(const MaxAlgMatrixXd& matrixXd);
std::ostream& operator<<(std::ostream & stream, const MaxAlgMatrixXd& matrixXd);
MaxAlgMatrixXd power(const MaxAlgMatrixXd &matrixXd, int n = 1);
MaxAlgMatrixXd clini(const MaxAlgMatrixXd &matrixXd);
double spectral_radius(const MaxAlgMatrixXd &matrixXd);
double SpectralRadiusAdvance(const MaxAlgMatrixXd & matrixXd);



inline double d(double p, double q) {
    // Assert(q != 0, "Division by zero");
    return p / q;
}

#endif //TROPICAL_TROPICAL_H
