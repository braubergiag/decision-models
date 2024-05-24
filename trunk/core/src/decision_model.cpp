#include "../include/decision_model.h"
#include <algorithm>

void DecisionModel::addAlternative(const std::string &alternative) {
	alternativesNames_.emplace_back(alternative);
}

void DecisionModel::addCriteria(const std::string &criteria) {
	criteriaNames_.emplace_back(criteria);
}

void DecisionModel::setDecisionName(const std::string &decisionName) {
	decisionName_ = decisionName;
}

const std::string &DecisionModel::decisionName() const {
	return decisionName_;
}

const std::vector<std::string> &DecisionModel::criteriaNames() const {
	return criteriaNames_;
}

const std::vector<std::string> &DecisionModel::alternativesNames() const {
	return alternativesNames_;
}

void DecisionModel::setCriteriaNames(const std::vector<std::string> &criteriaNames) {
	criteriaNames_ = criteriaNames;
}

void DecisionModel::setAlternativesNames(const std::vector<std::string> &alternativesNames) {
	alternativesNames_ = alternativesNames;
}

const Eigen::MatrixXd &DecisionModel::criteriaComparisons() const {
	return criteriaComparisons_;
}

void DecisionModel::setCriteriaComparisons(const Eigen::MatrixXd &criteriaComparisons,
										   const ComparisionMatrixView &criteriaMatrixView) {
	criteriaComparisons_ = criteriaComparisons;
	criteriaComparisonsMatrixView_ = criteriaMatrixView;
	criteriaComparisonMatrixIsInit_ = true;
}

const std::vector<Eigen::MatrixXd> &DecisionModel::alternativesComparisons() const {
	return alternativesComps_;
}

void DecisionModel::setAlternativesComparisons(const std::vector<Eigen::MatrixXd> &alternativesComparisons) {
	alternativesComps_ = alternativesComparisons;
}

int DecisionModel::criteriaCount() const {
	return criteriaNames_.size();
}

int DecisionModel::alternativesCount() const {
	return alternativesNames_.size();
}

bool DecisionModel::criteriaComparisonMatrixIsInit() const {
	return criteriaComparisonMatrixIsInit_;
}

const DecisionModel::ComparisonMatrixView &DecisionModel::criteriaComparisonsMatrixView() const {
	return criteriaComparisonsMatrixView_;
}

void DecisionModel::setAlternativesCompsAt(const Eigen::MatrixXd &alternativesComps,
										   const ComparisionMatrixView &alternativesCompsView, int index) {
	if (alternativesComps_.size() != criteriaCount()) {
		alternativesComps_.resize(criteriaCount());
		alternativesCompsViews_.resize(criteriaCount());
		alternativesCompsIsInit_.resize(criteriaCount());
	}
	alternativesComps_.at(index) = alternativesComps;
	alternativesCompsViews_.at(index) = alternativesCompsView;
	alternativesCompsIsInit_.at(index) = true;
}

const ComparisionMatrixView &DecisionModel::compsViewAt(int index) const {
	return alternativesCompsViews_.at(index);
}

const Eigen::MatrixXd &DecisionModel::compsAt(int index) const {
	return alternativesComps_.at(index);
}

bool DecisionModel::compsIsInitAt(int index) const {
	if (index < alternativesCompsIsInit_.size())
		return alternativesCompsIsInit_.at(index);
	return false;
}

void DecisionModel::performTropicalMethod() {
	tropicalDecisionMethod_ = tropical_decision_method(alternativesComps_, criteriaComparisons_);
	tropicalDecisionMethod_.perform();
}

bool DecisionModel::alternativesComparisonsMatricesIsInit() const {

	return alternativesCompsIsInit_.size() == criteriaCount() &&
		   std::all_of(begin(alternativesCompsIsInit_), end(alternativesCompsIsInit_),
					   [](bool isInit) { return isInit; });
}

void DecisionModel::performAhpMethod() {
	ahpDecisionMethod_ = ahp_decision_method(alternativesComps_, criteriaComparisons_);
	ahpDecisionMethod_.perform();
}

void DecisionModel::performGmMethod() {
	gmDecisionMethod_ = gm_decision_method(alternativesComps_, criteriaComparisons_);
	gmDecisionMethod_.perform();
}

std::string DecisionModel::ahpResult() const {
	auto res = ahpDecisionMethod_.final_weights();
	std::stringstream ss;
	ss << res;
	ss << modelRanking(res);
	return ss.str();
}

std::string DecisionModel::gmResult() const {
	auto res = gmDecisionMethod_.final_weights();
	std::stringstream ss;
	ss << res;
	ss << modelRanking(res);
	return ss.str();
}

std::pair<std::string, std::string> DecisionModel::tropicalResult() const {
	// TODO Add Ranking
	auto [best_vectors, worst_vector] = tropicalDecisionMethod_.final_weights();
	std::stringstream ss_best, ss_worst;
	for (size_t i = 0, sz = best_vectors.size(); i < sz; ++i) {
		ss_best << best_vectors[i];
		ss_best << (i + 1 < sz ? "\n\n" : "");
		ss_best << modelRanking(best_vectors[i]);
	}
	ss_worst << worst_vector;
	ss_worst << modelRanking(worst_vector);
	return {ss_best.str(), ss_worst.str()};
}

std::string DecisionModel::modelRanking(const Eigen::VectorXd &weights) const {
	std::vector<std::pair<double, int>> rankings;
	for (int i = 0; i < weights.size(); ++i) {
		rankings.emplace_back(weights(i), i + 1);
	}
	std::sort(begin(rankings), end(rankings), std::greater{});

	std::stringstream ss;
	ss << "\n\n";
	for (int i = 0; i < rankings.size(); ++i) {
		auto alternative = rankings.at(i).second;
		ss << "A" + std::to_string(alternative) + (i + 1 < rankings.size() ? " > " : "");
	}
	return ss.str();
}