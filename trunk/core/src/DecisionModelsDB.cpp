#include "../include/DecisionModelsDB.h"

void DecisionModelsDB::addOrUpdateModel(const std::string &modelName, const DecisionModel &decisionModel) {
	modelsDb_[modelName] = decisionModel;
}

size_t DecisionModelsDB::size() const {
	return modelsDb_.size();
}

bool DecisionModelsDB::count(const std::string &modelName) const {
	return modelsDb_.count(modelName);
}

const DecisionModel &DecisionModelsDB::model(const std::string &modelName) const {
	return modelsDb_.at(modelName);
}

DecisionModel &DecisionModelsDB::model(const std::string &modelName) {
	return modelsDb_.at(modelName);
}

void DecisionModelsDB::deleteModel(const std::string &modelName) {
	if (modelsDb_.count(modelName))
		modelsDb_.erase(modelName);
}
