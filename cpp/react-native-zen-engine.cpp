#include "react-native-zen-engine.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

namespace zenengine {
  std::vector<rnzensdk::ZenEngineStruct*> engines;
  std::vector<rnzensdk::ZenDecisionStruct*> decisions;

  bool engineMatches(const rnzensdk::ZenEngineStruct* engine, const rnzensdk::ZenEngineStruct* _engine) {
    return std::memcmp(engine->_data, _engine->_data, sizeof(engine->_data)) == 0;
  }
  
  bool decisionMatches(const rnzensdk::ZenDecisionStruct* decision, const rnzensdk::ZenDecisionStruct* _decision) {
    return std::memcmp(decision->_data, _decision->_data, sizeof(decision->_data)) == 0;
  }

  rnzensdk::ZenEngineStruct* engineCreate() {
    rnzensdk::ZenEngineStruct* engine = rnzensdk::zen_engine_new();

    engines.push_back(engine);
    return engine;
  }
  
  rnzensdk::ZenDecisionStruct* decisionCreate(const rnzensdk::ZenEngineStruct* engine, const char* content) {
    auto it = std::find_if(engines.begin(), engines.end(),
      [&engine](rnzensdk::ZenEngineStruct* nextEngine) {
        return engineMatches(nextEngine, engine);
      });

    if (it == engines.end()) {
      return nullptr;
    }

    const struct rnzensdk::ZenResult_ZenDecisionStruct decision = rnzensdk::zen_engine_create_decision(
      *it, reinterpret_cast<const char*>(content));

    decisions.push_back(decision.result);
    return decision.result;
  }
  
  rnzensdk::ZenResult_c_char evaluationCreate(const rnzensdk::ZenDecisionStruct* decision, const char* context) {
    auto it = std::find_if(decisions.begin(), decisions.end(),
      [&decision](rnzensdk::ZenDecisionStruct* nextDecision) {
        return decisionMatches(nextDecision, decision);
      });

    if (it == decisions.end()) {
      return rnzensdk::ZenResult_c_char{};
    }

    rnzensdk::ZenEngineEvaluationOptions options = {
      .max_depth = 10
    };

    struct rnzensdk::ZenResult_c_char evaluation = rnzensdk::zen_decision_evaluate(
      *it, reinterpret_cast<const char*>(context), options);

    return evaluation;
  }
  
  void engineFree(rnzensdk::ZenEngineStruct* engine) {
    if (engine == nullptr) {
      std::cout << "Null engine pointer provided." << std::endl;
      return;
    }

    auto it = std::remove_if(engines.begin(), engines.end(),
      [&engine](rnzensdk::ZenEngineStruct* nextEngine) {
        return engineMatches(nextEngine, engine);
      });

    if (it == engines.end()) {
      std::cout << "Engine not found." << std::endl;
    }

    engines.erase(it, engines.end());
  }

  void engineFreeAll() {
    for (auto engine : engines) {
      if (engine != nullptr) {
        rnzensdk::zen_engine_free(engine);
      }
    }
    engines.clear();
  }

  void decisionFree(rnzensdk::ZenDecisionStruct* decision) {
    if (decision == nullptr) {
      std::cout << "Null decision pointer provided." << std::endl;
      return;
    }

    auto it = std::remove_if(decisions.begin(), decisions.end(),
      [&decision](rnzensdk::ZenDecisionStruct* nextDecision) {
        return decisionMatches(nextDecision, decision);
      });

    if (it == decisions.end()) {
      std::cout << "Decision not found." << std::endl;
    }

    decisions.erase(it, decisions.end());
  }

  void decisionFreeAll() {
    for (auto decision : decisions) {
      if (decision != nullptr) {
        zen_decision_free(decision);
      }
    }
    decisions.clear();
    std::cout << "All decisions freed." << std::endl;
  }
}
