#include <Thread.h>
#include <ThreadController.h>

#define LOW_TEMP_THRESHOLD 25


ThreadController threadController = ThreadController();

Thread* tempThread = new Thread();

void setup(void) {
  Serial.begin(115200);

  setupWifi();
  setupDS18B20(LOW_TEMP_THRESHOLD);

  tempThread->onRun(runTemp);
  tempThread->setInterval(10000);

  threadController.add(tempThread);

}

void loop(void) {
  threadController.run();

  loopWifi();
}
