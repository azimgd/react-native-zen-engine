package com.zenengine

import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.module.annotations.ReactModule
import com.facebook.react.bridge.ReactMethod

@ReactModule(name = ZenEngineModule.NAME)
class ZenEngineModule(reactContext: ReactApplicationContext) :
  NativeZenEngineSpec(reactContext) {

  override fun getName(): String {
    return NAME
  }

  private external fun nativeEngineCreate(): Double
  private external fun nativeDecisionCreate(engineId: Double, content: String): Double
  private external fun nativeEvaluationCreate(decisionId: Double, context: String): String
  private external fun nativeEngineFree(engineId: Double)
  private external fun nativeDecisionFree(decisionId: Double)

  @ReactMethod(isBlockingSynchronousMethod = true)
  override fun engineCreate(): Double {
    return nativeEngineCreate()
  }

  @ReactMethod
  override fun engineFree(engineId: Double) {
    nativeEngineFree(engineId)
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  override fun decisionCreate(engineId: Double, content: String): Double {
    return nativeDecisionCreate(engineId, content)
  }

  @ReactMethod
  override fun decisionFree(decisionId: Double) {
    nativeDecisionFree(decisionId)
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  override fun evaluationCreate(decisionId: Double, context: String): String {
    return nativeEvaluationCreate(decisionId, context)
  }

  companion object {
    const val NAME = "ZenEngine"

    init {
      System.loadLibrary("react-native-zen-engine")
    }
  }
}
