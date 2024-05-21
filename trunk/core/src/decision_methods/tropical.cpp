#include "../../include/decision_methods/tropical.h"

std::ostream &operator<<(std::ostream &stream, const MaxAlgMatrixXd &matrixXd) {
	return stream << matrixXd.cast<double>();
}

double spectral_radius(const MaxAlgMatrixXd &mat) {
	double max_trace = mat.trace();
	MaxAlgMatrixXd curr_matrix = mat;
	for (auto i = 1; i < mat.rows(); ++i) {
		curr_matrix *= mat;
		max_trace = std::max(max_trace, pow(curr_matrix.trace(), d(1, i + 1)));
	}
	return max_trace;
}

MaxAlgMatrixXd kleene_star(const MaxAlgMatrixXd &mat) {
	MaxAlgMatrixXd res_matrix = MaxAlgMatrixXd::Identity(mat.rows(), mat.cols());
	MaxAlgMatrixXd curr_matrix = mat;
	res_matrix += curr_matrix;
	for (int i = 1; i < res_matrix.cols() - 1; ++i) {
		curr_matrix *= mat;
		res_matrix += curr_matrix;
	}
	return res_matrix;
}
