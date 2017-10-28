#define ANALOG_IN A0

int _calibrationAnalogHighReading = 1024;
int _calibrationAnalogLowReading = 0;

int _lastSoilMoisture;

void setupSoil(int calibrationAnalogHighReading,
               int calibrationAnalogLowReadirng) {
  _calibrationAnalogHighReading = calibrationAnalogHighReading;
  _calibrationAnalogLowReading = calibrationAnalogLowReadirng;
}

void runSoil(void) {
  updateSoilMoisture();
  int soilMoisture = getSoilMoisture();
  Serial.print("Soil moisture is: ");
  Serial.print(soilMoisture);
  Serial.println("%");
}

void updateSoilMoisture(void) {
  int analogOutput = analogRead(ANALOG_IN);
  Serial.print("updateSoilMoisture analogOutput: ");
  Serial.println(analogOutput);

  _lastSoilMoisture = map(analogOutput,
                          _calibrationAnalogHighReading, _calibrationAnalogLowReading,
                          0, 100);
}

float getSoilMoisture(void) {
  return _lastSoilMoisture;
}
