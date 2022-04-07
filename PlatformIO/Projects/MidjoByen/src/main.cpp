#include "LineFollower.h"
#include "SW_Battery.h"
#include "common.h"

LineFollower ln;
carController cc;

unsigned long runTime = 0;
unsigned long clearTime = 0;

void setup()
{
  ln.startUpSequence();
  runTime = millis();
  clearTime = millis();
}

void loop()
{
  int charge = cc.calculatePowerConsumption(cc.getCarDistance());

  if (charge > 0)
  {
    encoders.init();
    ln.checkForTurn(0, 1, 3);
    ln.checkForTurn(3, 4, 1);
    ln.lineFollower();
    ln.endOfLine();
  }

  else if (charge <= 0)
  {
    motors.setSpeeds(0, 0);
  }

  if (millis() - runTime >= 1000)
  {
    cc.updateDisplayInformation(String(charge));
    runTime = millis();
  }
  if (millis() - clearTime >= 2000)
  {
    lcd.clear();
    clearTime = millis();
  }
}
