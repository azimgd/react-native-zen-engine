#include <jni.h>
#include "react-native-zen-engine.h"
#include "rnzensdk.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_zenengine_ZenEngineModule_nativeEngineCreate(JNIEnv *env, jobject type) {
    return zenengine::engineCreate()->_data[0];
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_zenengine_ZenEngineModule_nativeDecisionCreate(JNIEnv *env, jobject type, jdouble engineId, jstring content) {
    rnzensdk::ZenEngineStruct engine = rnzensdk::ZenEngineStruct{};
    engine._data[0] = (uint8_t)engineId;

    rnzensdk::ZenDecisionStruct* decision = zenengine::decisionCreate(&engine, env->GetStringUTFChars(content, nullptr));
    return zenengine::engineCreate()->_data[0];
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_zenengine_ZenEngineModule_nativeEvaluationCreate(JNIEnv *env, jobject type, jdouble decisionId, jstring context) {
    rnzensdk::ZenDecisionStruct decision = rnzensdk::ZenDecisionStruct{};
    decision._data[0] = (uint8_t)decisionId;

    rnzensdk::ZenResult_c_char evaluation = zenengine::evaluationCreate(&decision, env->GetStringUTFChars(context, nullptr));
    return env->NewStringUTF(evaluation.result);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zenengine_ZenEngineModule_nativeEngineFree(JNIEnv *env, jobject type, jdouble engineId) {
    rnzensdk::ZenEngineStruct engine = rnzensdk::ZenEngineStruct{};
    engine._data[0] = (uint8_t)engineId;

    zenengine::engineFree(&engine);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zenengine_ZenEngineModule_nativeDecisionFree(JNIEnv *env, jobject type, jdouble decisionId) {
    rnzensdk::ZenDecisionStruct decision = rnzensdk::ZenDecisionStruct{};
    decision._data[0] = (uint8_t)decisionId;

    zenengine::decisionFree(&decision);
}
