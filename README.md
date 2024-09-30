# react-native-zen-engine

react-native-zen-engine

## Installation

```sh
npm install react-native-zen-engine
```

## Usage


```js
import * as ZenEngine from 'react-native-zen-engine';

const engineId = ZenEngine.engineCreate();
const decisionId = ZenEngine.decisionCreate(engineId, sampleDecision);
const evalauation = ZenEngine.evaluationCreate(decisionId, sampleContext);

ZenEngine.decisionFree(decisionId);
ZenEngine.engineFree(engineId);
```

## Build
```
yarn
cd zenffi

// android
export PATH="~/Library/Android/sdk/ndk/23.1.7779620/toolchains/llvm/prebuilt/darwin-x86_64/bin:$PATH"
make android
cd example
npm run android

// iOS
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

make ios
cd example/ios
pod install
cd example
npm run ios
```

## License

MIT
