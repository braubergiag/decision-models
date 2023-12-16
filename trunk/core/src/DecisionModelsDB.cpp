#include "../include/DecisionModelsDB.h"

void DecisionModelsDB::addModel(const string &modelName, const DecisionModel &decisionModel) {
    modelsDb_[modelName] = decisionModel;
}
