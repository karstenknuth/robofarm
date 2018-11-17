# include "ArduinoUtil.h"

static void ArduinoUtil::initSerial(int uploadSpeed)
{
  Serial.begin(uploadSpeed);
  Serial.setTimeout(2000);

  // Wait for serial to initialize
  while (!Serial) {}
}

