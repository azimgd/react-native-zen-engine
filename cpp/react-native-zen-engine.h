#ifndef ZENENGINE_H
#define ZENENGINE_H

#include "rnzensdk.h"

namespace zenengine {
   rnzensdk::ZenEngineStruct* engineCreate();
   void engineFree(rnzensdk::ZenEngineStruct* engine);

   rnzensdk::ZenDecisionStruct* decisionCreate(const rnzensdk::ZenEngineStruct* engine, const char* content);
   void decisionFree(rnzensdk::ZenDecisionStruct* decision);

   rnzensdk::ZenResult_c_char evaluationCreate(const rnzensdk::ZenDecisionStruct* decision, const char* context);
}

#endif /* ZENENGINE_H */
