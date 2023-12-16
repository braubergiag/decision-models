#pragma once
#include <map>
#include <string>
#include "DecisionModel.h"
class DecisionModelsDB {
public:
    void addModel(const std::string& modelName, const DecisionModel & decisionModel);

private:
    using model_name = std::string;
    std::map<model_name,DecisionModel> modelsDb_;
};

