#include "../../include/decision_methods/tropical.h"
#include "../../include/decision_methods/utils.h"

using utils::d;

namespace tropical {

	std::ostream &operator<<(std::ostream &stream, const MaxAlgMatrixXd &matrixXd) {
		return stream << matrixXd.cast<double>();
	}

	bool operator>=(const MaxAlgVectorXd &lhs, const MaxAlgVectorXd &rhs) {
		Eigen::Index sz = std::max(lhs.size(), rhs.size());
		for (Eigen::Index i = 0; i < sz; ++i) {
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
		MaxAlgMatrixXd res_matrix = eye(mat.rows(), mat.cols());
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

	MaxAlgMatrixXd to_MaxAlgMatrixXd(const Eigen::MatrixXd &mat) {
		auto maxAlgMatrixXd = eye(mat.rows(), mat.cols());
		for (auto row = 0; row < mat.rows(); ++row) {
			for (auto column = 0; column < mat.cols(); ++column) {
				maxAlgMatrixXd(row, column) = mat(row, column);
			}
		}
		return maxAlgMatrixXd;
	}

	Eigen::MatrixXd to_MatrixXd(const MaxAlgMatrixXd &maxAlgMatrixXd) {
		Eigen::MatrixXd matrixXd = Eigen::MatrixXd::Zero(maxAlgMatrixXd.rows(), maxAlgMatrixXd.cols());
		for (auto row = 0; row < maxAlgMatrixXd.rows(); ++row) {
			for (auto column = 0; column < maxAlgMatrixXd.cols(); ++column) {
				matrixXd(row, column) = maxAlgMatrixXd(row, column);
			}
		}
		return matrixXd;
	}

	Eigen::VectorXd to_VectorXd(const MaxAlgVectorXd &maxAlgVectorXd) {
		Eigen::VectorXd vectorXd = Eigen::VectorXd::Zero(maxAlgVectorXd.size());
		for (auto i = 0; i < maxAlgVectorXd.rows(); ++i) {
			vectorXd(i) = maxAlgVectorXd(i);
		}
		return vectorXd;
	}

	MaxAlgMatrixXd eye(Eigen::Index rows, Eigen::Index cols) {
		return MaxAlgMatrixXd::Identity(rows, cols);
	}

	MaxAlgMatrixXd eye(Eigen::Index n) {
		return MaxAlgMatrixXd::Identity(n, n);
	}

	MaxAlgVectorXd ones(Eigen::Index n) {
		return MaxAlgVectorXd::Ones(n);
	}
} // namespace tropical
