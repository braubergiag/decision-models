#pragma once

#include <map>
#include <string>
#include <Eigen/Core>
#include <decision_model.h>

class DecisionModelsDB {

public:
	void addOrUpdateModel(const std::string &modelName, const DecisionModel &decisionModel);
	void changeModelName(const std::string &oldModelName, const std::string &newModelName);
	void deleteModel(const std::string &modelName);
	size_t size() const;
	bool count(const std::string &modelName) const;
	const DecisionModel &model(const std::string &modelName) const;
	DecisionModel &model(const std::string &modelName);

private:
	using ModelName = std::string;
	std::map<ModelName, DecisionModel> modelsDb_;
};
