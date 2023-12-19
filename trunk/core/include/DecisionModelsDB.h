#pragma once
#include <map>
#include <string>
#include "DecisionModel.h"
class DecisionModelsDB {

public:
    void addOrUpdateModel(const std::string &modelName, const DecisionModel & decisionModel);
    void deleteModel(const std::string& modelName);
    size_t size() const;
    bool count(const std::string & modelName) const;
    const DecisionModel& model(const std::string & modelName) const;

private:
    using ModelName = std::string;
    std::map<ModelName,DecisionModel> modelsDb_;
};


