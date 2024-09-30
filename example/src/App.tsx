import { StyleSheet, SafeAreaView, Text } from 'react-native';
import * as ZenEngine from 'react-native-zen-engine';
import sampleContext from './sampleContext.json';
import sampleDecision from './sampleDecision.json';

const engineId = ZenEngine.engineCreate();
const decisionId = ZenEngine.decisionCreate(engineId, sampleDecision);
const evalauation = ZenEngine.evaluationCreate(decisionId, sampleContext);

ZenEngine.decisionFree(decisionId);
ZenEngine.engineFree(engineId);

export default function App() {
  return (
    <SafeAreaView style={styles.container}>
      <Text style={styles.text}>
        ZenEngine Response: {JSON.stringify(evalauation, null, 2)}
      </Text>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: 'black',
  },
  text: {
    paddingHorizontal: 16,
    color: 'white',
  },
});
