#pragma once

#include <vector>
#include <string>
#include <Eigen/Core>
#include <ahp_decision_method.h>
#include <gm_decision_method.h>
#include <tropical_decision_method.h>

using ComparisionMatrixView = Eigen::Matrix<std::string, Eigen::Dynamic, Eigen::Dynamic>;

class DecisionModel {
public:
	using ComparisonMatrixView = Eigen::MatrixX<std::string>;
	DecisionModel() = default;

public:
	void addAlternative(const std::string &alternative);
	void addCriteria(const std::string &criteria);
	void removeAlternative(int index);
	void removeCriteria(int index);

private:
	template<typename T>
	Eigen::MatrixX<T> removeRow(const Eigen::MatrixX<T> &matrix, int index);
	template<typename T>
	Eigen::MatrixX<T> removeColumn(const Eigen::MatrixX<T> &matrix, int index);

public:
	void performTropicalMethod();
	void performAhpMethod();
	void performGmMethod();

	std::string ahpResult() const;
	std::string gmResult() const;
	std::pair<std::string, std::string> tropicalResult() const;

	using ModelRanking = std::vector<std::pair<double, int>>;
	static ModelRanking rankModel(const Eigen::VectorXd &weights);
	static std::string modelRanking(const ModelRanking &modelRanking);
	static std::string modelRanking(const Eigen::VectorXd &weights);

public:
	void setDecisionName(const std::string &decisionName);
	void setCriteriaNames(const std::vector<std::string> &criteriaNames);
	void setAlternativesNames(const std::vector<std::string> &alternativesNames);
	void setCriteriaComparisons(const Eigen::MatrixXd &criteriaComparisons,
								const ComparisionMatrixView &criteriaMatrixView);


	void setAlternativesComparisons(const std::vector<Eigen::MatrixXd> &alternativesComparisons);
	void setAlternativesCompsAt(const Eigen::MatrixXd &alternativesComps,
								const ComparisionMatrixView &alternativesCompsView, int index);

	const ComparisionMatrixView &compsViewAt(int index) const;
	const Eigen::MatrixXd &compsAt(int index) const;
	bool compsIsInitAt(int index) const;

public:
	const std::string &modelName() const;
	const std::vector<std::string> &criteriaNames() const;
	const std::vector<std::string> &alternativesNames() const;

	const Eigen::MatrixXd &criteriaComparisons() const;
	const ComparisonMatrixView &criteriaComparisonsMatrixView() const;
	bool criteriaComparisonMatrixIsInit() const;
	bool alternativesComparisonsMatricesIsInit() const;

	const std::vector<Eigen::MatrixXd> &alternativesComparisons() const;

	int criteriaCount() const;
	int alternativesCount() const;


public:
	constexpr static auto equality_sign = "\u2261";
	constexpr static auto greater_sign = "\u227B";
	constexpr static auto alternative_sign = "A";

private:
	std::string modelName_;
	std::vector<std::string> criteriaNames_;
	std::vector<std::string> alternativesNames_;

	ComparisonMatrixView criteriaComparisonsMatrixView_;
	Eigen::MatrixXd criteriaComparisons_;

	std::vector<Eigen::MatrixXd> alternativesComps_;
	std::vector<ComparisonMatrixView> alternativesCompsViews_;
	std::vector<bool> alternativesCompsIsInit_;


	bool criteriaComparisonMatrixIsInit_{false};
	bool alternativesComparisonsMatricesIsInit_{false};

	ahp_decision_method ahpDecisionMethod_;
	gm_decision_method gmDecisionMethod_;
	tropical_decision_method tropicalDecisionMethod_;
};

template<typename T>
Eigen::MatrixX<T> DecisionModel::removeColumn(const Eigen::MatrixX<T> &matrix, int index) {
	auto new_rows_count = matrix.rows();
	auto new_cols_count = matrix.cols() - 1;

	Eigen::MatrixX<T> result(new_rows_count, new_cols_count);
	result.leftCols(index) = matrix.leftCols(index);
	result.rightCols(matrix.cols() - index - 1) = matrix.rightCols(matrix.cols() - index - 1);
	return result;
}

template<typename T>
Eigen::MatrixX<T> DecisionModel::removeRow(const Eigen::MatrixX<T> &matrix, int index) {
	auto new_rows_count = matrix.rows() - 1;
	auto new_cols_count = matrix.cols();

	Eigen::MatrixX<T> result(new_rows_count, new_cols_count);
	result.topRows(index) = matrix.topRows(index);
	result.bottomRows(matrix.rows() - index - 1) = matrix.bottomRows(matrix.rows() - index - 1);
	return result;
}
