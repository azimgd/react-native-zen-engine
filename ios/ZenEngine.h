#ifdef __cplusplus
#import "react-native-zen-engine.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNZenEngineSpec.h"

@interface ZenEngine : NSObject <NativeZenEngineSpec>
#else
#import <React/RCTBridgeModule.h>

@interface ZenEngine : NSObject <RCTBridgeModule>
#endif

@end
