#include "../../include/decision_methods/tropical.h"

std::ostream &operator<<(std::ostream &stream, const MaxAlgMatrixXd &matrixXd) {
	return stream << matrixXd.cast<double>();
}

bool operator>=(const MaxAlgVectorXd &lhs, const MaxAlgVectorXd &rhs) {
	for (size_t i = 0, sz = std::max(lhs.size(), rhs.size()); i < sz; ++i) {
		if (lhs(i) < rhs(i))
			return false;
	}
	return true;
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

std::pair<bool, int> find_dominating_vector(const std::vector<MaxAlgVectorXd> &v) {
	for (auto i = 0; i < v.size(); ++i) {
		bool is_dominating = true;
		for (auto j = 0; j < v.size() && is_dominating; ++j) {
			if (v[i] >= v[j])
				continue;
			is_dominating = false;
		}
		if (is_dominating && v.size() > 1) {
			return {true, i};
		}
	}
	return {false, -1};
}

void remove_dominating_vectors(std::vector<MaxAlgVectorXd> &v) {
	auto [is_found, ind] = find_dominating_vector(v);
	while (is_found) {
		v.erase(v.begin() + ind);
		std::tie(is_found, ind) = find_dominating_vector(v);
	}
}