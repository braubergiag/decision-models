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
	void addAlternativeName(const std::string &alternative);
	void addCriteriaName(const std::string &criteria);
	void removeAlternative(int alternativeIndex);
	void removeCriteria(int criteriaIndex);
	void addAlternative(const std::string &alternativeName);
	void addCriteria(const std::string &criteriaName);

private:
	void initAlternativesComparisonsMatrix();

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
	constexpr static auto equalitySign = "\u2261";
	constexpr static auto greaterSign = "\u227B";
	constexpr static auto alternativeSign = "A";

private:
	constexpr static auto defaultMatrixValue = 1.;
	inline const static std::string defaultMatrixView = "1";

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
