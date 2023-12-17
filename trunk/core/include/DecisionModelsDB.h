#pragma once
#include <map>
#include <string>
#include "DecisionModel.h"
class DecisionModelsDB {
public:
    void addModel(const std::string& modelName, const DecisionModel & decisionModel);
    void deleteModel(const std::string& modelName);
    size_t size() const;
    bool count(const std::string & modelName) const;
    const DecisionModel& model(const std::string & modelName) const;

private:
    using model_name = std::string;
    std::map<model_name,DecisionModel> modelsDb_;
};


