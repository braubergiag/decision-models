#pragma once

#include <vector>
#include <string>
#include <Eigen/Core>
#include "decision_methods/ahp_decision_method.h"
#include "decision_methods/gm_decision_method.h"
#include "decision_methods/tropical_decision_method.h"

using ComparisionMatrixView = Eigen::Matrix<std::string, Eigen::Dynamic, Eigen::Dynamic>;

class DecisionModel {
public:
	using ComparisonMatrixView = Eigen::Matrix<std::string, Eigen::Dynamic, Eigen::Dynamic>;
	DecisionModel() = default;

public:
	void addAlternative(const std::string &alternative);
	void addCriteria(const std::string &criteria);

public:
	void performTropicalMethod();
	void performAhpMethod();
	void performGmMethod();

	std::string ahpResult() const;
	std::string gmResult() const;
	std::pair<std::string, std::string> tropicalResult() const;
	std::string modelRanking(const VectorXd & weights) const;

public:
	void setDecisionName(const std::string &decisionName);
	void setCriteriaNames(const std::vector<std::string> &criteriaNames);
	void setAlternativesNames(const std::vector<std::string> &alternativesNames);
	void setCriteriaComparisons(const Eigen::MatrixXd &criteriaComparisons, const ComparisionMatrixView &criteriaMatrixView);


	void setAlternativesComparisons(const std::vector<Eigen::MatrixXd> &alternativesComparisons);
	void setAlternativesCompsAt(const Eigen::MatrixXd &alternativesComps,
								const ComparisionMatrixView &alternativesCompsView, int index);

	const ComparisionMatrixView &compsViewAt(int index) const;
	const Eigen::MatrixXd &compsAt(int index) const;
	bool compsIsInitAt(int index) const;

public:
	const std::string &decisionName() const;
	const std::vector<std::string> &criteriaNames() const;
	const std::vector<std::string> &alternativesNames() const;

	const Eigen::MatrixXd &criteriaComparisons() const;
	const ComparisonMatrixView &criteriaComparisonsMatrixView() const;
	bool criteriaComparisonMatrixIsInit() const;
	bool alternativesComparisonsMatricesIsInit() const;

	const std::vector<Eigen::MatrixXd> &alternativesComparisons() const;

	int criteriaCount() const;
	int alternativesCount() const;


private:
	std::string decisionName_;
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
