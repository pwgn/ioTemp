#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_DS18B20_BUS D7
#define DS18B20_LED_PIN D6

OneWire oneWireDS18B20(ONE_WIRE_DS18B20_BUS);
DallasTemperature DS18B20(&oneWireDS18B20);

float _lastTemperature;
float _lowTempThreshold = 25;

void setupDS18B20(float lowTempThreshold)
{
  _lowTempThreshold = lowTempThreshold;

  pinMode(DS18B20_LED_PIN, OUTPUT);
  DS18B20.begin();
}

void runTemp(void) {
  Serial.println("Requesting temperatures...");

  updateDS18B20Temperature();
  float temperature = getDS18B20Temperature();
  setDS18B20Led(temperature);

  Serial.print("Temperature is: ");
  Serial.println(temperature);
  Serial.println("");
}

void updateDS18B20Temperature(void) {
  DS18B20.requestTemperatures();
  _lastTemperature = DS18B20.getTempCByIndex(0);
}

float getDS18B20Temperature(void) {
  return _lastTemperature;
}

void setDS18B20Led(int temperature) {
  if (temperature < _lowTempThreshold) {
    digitalWrite(DS18B20_LED_PIN, HIGH);
  } else {
    digitalWrite(DS18B20_LED_PIN, LOW);
  }
}
