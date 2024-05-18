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
	explicit operator T() const noexcept { return scalar; }

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
	friend MaxAlg operator-=(MaxAlg left, MaxAlg right) noexcept { return left; }
	friend MaxAlg operator*(MaxAlg left, MaxAlg right) noexcept {
		left *= right;
		return left;
	}
	friend MaxAlg operator-(MaxAlg left, MaxAlg right) noexcept { return left; }
	friend MaxAlg operator/(MaxAlg left, MaxAlg right) noexcept {
		left /= right;
		return left;
	}
	friend bool operator==(MaxAlg left, MaxAlg right) noexcept { return left.scalar == right.scalar; }
	friend bool operator!=(MaxAlg left, MaxAlg right) noexcept { return left.scalar != right.scalar; }
	friend bool operator>(MaxAlg left, MaxAlg right) noexcept { return left.scalar > right.scalar; }
	friend bool operator>=(MaxAlg left, MaxAlg right) noexcept { return left.scalar >= right.scalar; }
	friend bool operator<(MaxAlg left, MaxAlg right) noexcept { return left.scalar < right.scalar; }
	friend bool operator<=(MaxAlg left, MaxAlg right) noexcept { return left.scalar <= right.scalar; }
	friend std::ostream &operator<<(std::ostream &stream, MaxAlg right) noexcept { return stream << right.scalar; }
};


template<class T>
double sqrt(const MaxAlg<T> &val) {
	return ::sqrt(val.scalar);
}


template<class T, Eigen::Index Rows, Eigen::Index Cols>
using MaxAlgMatrix = Eigen::Matrix<MaxAlg<T>, Rows, Cols>;

template<class T, Eigen::Index Rows, Eigen::Index Cols>
using MaxAlgArray = Eigen::Array<MaxAlg<T>, Rows, Cols>;


#if 0

MatrixXd MultiplyMaxAlgMat(const MaxAlgMatrixXd& a,const MaxAlgMatrixXd& b){
    MaxAlgMatrixXd c(a.rows(),b.cols());
    for (uint i = 0; i < a.rows(); ++i) {
        for (uint j = 0; j < b.cols(); ++j) {
            std::vector<double> values;
            for (uint k = 0; k < a.cols(); ++k) {
                values.push_back((a(i, k) * b(k, j)).scalar);
            }

            c(i,j) = *std::max_element(begin(values),end(values));
        }
    }

    return c.cast<double>();

}
MatrixXd AddMaxAlgMat(const MaxAlgMatrixXd& a,const MaxAlgMatrixXd& b) {
    MaxAlgMatrixXd c(a.rows(),a.cols());
    for (uint i = 0; i < a.rows(); ++i) {
        for (uint j = 0; j < a.cols(); ++j) {
            c(i,j) = std::max(a(i,j),b(i,j));
        }
    }

    return c.cast<double>();
}
MatrixXd GetSumMatrix(const MaxAlgMatrixXd & x,const MaxAlgMatrixXd & y) {
    MaxAlgMatrixXd r(2,2);

    r(0,0)  = max(x(0,0),y(0,0));
    r(0,1) =  max(x(0,1),y(0,1));
    r(1,0) = max(x(1,0),y(1,0));
    r(1,1) =  max(x(1,1),y(1,1));


    return  r.cast<double>();
}
MatrixXd GetMultipliedMatrix(const MaxAlgMatrixXd & x,const MaxAlgMatrixXd & y) {
    MaxAlgMatrixXd r(2,2);
    r(0,0)  = max(x(0,0)*y(0,0),x(0,1)*y(1,0));
    r(0,1) = max(x(0,0)*y(0,1),x(0,1)*y(1,1));
    r(1,0) = max(x(1,0)*y(0,0),x(1,1)*y(1,0));
    r(1,1) = max(x(1,0)*y(0,1),x(1,1)*y(1,1));
    return  r.cast<double>();
}


void TestMatrixAddition(){
    MaxAlgMatrixXd x(2,2);
    MaxAlgMatrixXd y(2,2);
    mt19937 gen;
    uniform_real_distribution<> unif(-10,10);
    uint test_count = 100;
    for (auto i = 0; i < test_count; ++i)
    {

        x << unif(gen) , unif(gen),
                unif(gen) , unif(gen);
        y << unif(gen), unif(gen),
                unif(gen),unif(gen);

        AssertEqual((x + y).cast<double>(),GetSumMatrix(x,y), "TestMatrixAddition " +  std::to_string(i + i));
    }


}



void TestMatrixMultiplication(){
    MaxAlgMatrixXd x(2,2);
    MaxAlgMatrixXd y(2,2);
    mt19937 gen;
    uniform_real_distribution<> unif(-10,10);
    uint test_count = 100;
    for (auto i = 0; i < test_count; ++i) {

        x << unif(gen), unif(gen),
                unif(gen), unif(gen);
        y << unif(gen), unif(gen),
                unif(gen), unif(gen);

        AssertEqual((x * y).cast<double>(), GetMultipliedMatrix(x, y), "TestMatrixMultiplication " + std::to_string(i + i) );
    }


}
#endif
