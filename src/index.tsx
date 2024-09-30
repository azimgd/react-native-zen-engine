const ZenEngine = require('./NativeZenEngine').default;

type SampleInput = { [key: string]: any };
type SampleOutput = { [key: string]: any };

export function engineCreate(): number {
  const response = ZenEngine.engineCreate();
  return response;
}

export function engineFree(engineId: number): void {
  const response = ZenEngine.engineFree(engineId);
  return response;
}

export function decisionCreate(engineId: number, content: SampleInput): number {
  const contentRequest = JSON.stringify(content);
  const response = ZenEngine.decisionCreate(engineId, contentRequest);
  return response;
}

export function decisionFree(decisionId: number): void {
  const response = ZenEngine.decisionFree(decisionId);
  return response;
}

export function evaluationCreate(
  decisionId: number,
  context: SampleInput
): SampleOutput {
  const contextRequest = JSON.stringify(context);
  const response = ZenEngine.evaluationCreate(decisionId, contextRequest);
  return JSON.parse(response);
}
