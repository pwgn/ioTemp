#include <Thread.h>
#include <ThreadController.h>

#define LOW_TEMP_THRESHOLD 19

int CALIBRATION_ANALOG_HIGH_READING 970;
int CALIBRATION_ANALOG_LOW_READING 320;


ThreadController threadController = ThreadController();

Thread* tempThread = new Thread();
Thread* soilThread = new Thread();

void setup(void) {
  Serial.begin(115200);

  setupWifi();
  setupDS18B20(LOW_TEMP_THRESHOLD);
  setupSoil(CALIBRATION_ANALOG_HIGH_READING,
            CALIBRATION_ANALOG_LOW_READING);

  tempThread->onRun(runTemp);
  tempThread->setInterval(10000);

  soilThread->onRun(runSoil);
  soilThread->setInterval(1000);

  threadController.add(tempThread);
  threadController.add(soilThread);

}

void loop(void) {
  threadController.run();

  loopWifi();
}
