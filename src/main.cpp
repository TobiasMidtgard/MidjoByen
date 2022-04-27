// Include the library containing variables, libraries and functions.
#include "common.h"

// Create a new class for the linefollower and the carController.
LineFollower ln;
carController cc;

// constant value for when the user should be notified about the battery level.
const int dangerZone = 10;

unsigned long runTime = 0;
unsigned long clearTime = 0;

// Battery charge left in %.
int charge = 100;

// setup() is called once at the start of the program.
void setup()
{
  // calibrates the Zumo32u4 and waits for the user's input before continuing.
  // ln.init();

  runTime = millis();
  clearTime = millis();
}

// loop() is called in an endless loop.
void loop()
{
  // Get the carge left in %.
  // charge = cc.calculatePowerConsumption(charge, dangerZone);
  if (charge > 0)
  {
    // encoders.init();
    // ln.checkForTurn(0, 1, 3);
    // ln.checkForTurn(3, 4, 1);
    // ln.lineFollower();
    // ln.endOfLine();;
    motors.setSpeeds(speedValue, speedValue);
  }

  else if (charge <= 0)
  {
    motors.setSpeeds(0, 0);
  }

  String displayText = String((cc.calculateSpeedOverPercent(70, true)));

  if (millis() - runTime >= 1000)
  {
    charge = cc.calculatePowerConsumption(charge, dangerZone);
    cc.updateDisplayInformation(displayText);
    runTime = millis();
  }

  if (millis() - clearTime >= 2000)
  {
    lcd.clear();
    clearTime = millis();
  }
}
