#include <Wire.h>
#include "LineFollower.h"
#include "SW_Battery.h"
#include "common.h"

int drivingSpeed = 400;

LineFollower ln;
carController cc;

int runTime = 0;

void setup()
{
  // ln.startUpSequence();
  buttonA.waitForButton();
  runTime = millis();
}

void loop()
{
  encoders.init();
  motors.setSpeeds(drivingSpeed, drivingSpeed);
  float carDistance = cc.getCarDistance();
  float batteryLeft = cc.calculatePowerConsumption(carDistance);
  // if (batteryLeft <= 0)
  // {
  //   drivingSpeed = 0;
  // }
  float speed = cc.calculateCarSpeed();
  cc.updateDisplayInformation(String(carDistance), 100);
}