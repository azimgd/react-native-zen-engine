#import "ZenEngine.h"

@implementation ZenEngine
RCT_EXPORT_MODULE()

#ifdef RCT_NEW_ARCH_ENABLED
- (NSNumber *)engineCreate {
  rnzensdk::ZenEngineStruct *engine = zenengine::engineCreate();
  return [NSNumber numberWithUnsignedChar:engine->_data[0]];
}

- (NSNumber *)decisionCreate:(double)engineId content:(NSString *)content {
  rnzensdk::ZenEngineStruct engine = rnzensdk::ZenEngineStruct{};
  engine._data[0] = (uint8_t)engineId;
  
  rnzensdk::ZenDecisionStruct* decision = zenengine::decisionCreate(&engine, [content UTF8String]);
  return [NSNumber numberWithUnsignedChar:decision->_data[0]];
}

- (NSString *)evaluationCreate:(double)decisionId context:(NSString *)context {
  rnzensdk::ZenDecisionStruct decision = rnzensdk::ZenDecisionStruct{};
  decision._data[0] = (uint8_t)decisionId;

  rnzensdk::ZenResult_c_char evaluation = zenengine::evaluationCreate(&decision, [context UTF8String]);
  return @(evaluation.result);
}

- (void)engineFree:(double)engineId {
  rnzensdk::ZenEngineStruct engine = rnzensdk::ZenEngineStruct{};
  engine._data[0] = (uint8_t)engineId;

  zenengine::engineFree(&engine);
}

- (void)decisionFree:(double)decisionId {
  rnzensdk::ZenDecisionStruct decision = rnzensdk::ZenDecisionStruct{};
  decision._data[0] = (uint8_t)decisionId;
  
  zenengine::decisionFree(&decision);
}

- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
  (const facebook::react::ObjCTurboModule::InitParams &)params
{
  return std::make_shared<facebook::react::NativeZenEngineSpecJSI>(params);
}
#endif

@end
