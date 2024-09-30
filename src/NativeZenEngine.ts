import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  engineCreate(): number;
  engineFree(engineId: number): void;
  decisionCreate(engineId: number, content: string): number;
  decisionFree(decisionId: number): void;
  evaluationCreate(decisionId: number, context: string): string;
}

export default TurboModuleRegistry.getEnforcing<Spec>('ZenEngine');
