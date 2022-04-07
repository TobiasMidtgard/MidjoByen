#include "SW_Battery.h"
#include <Arduino.h>
#include <Wire.h>
#include <Zumo32U4.h>
#include "common.h"

static int rightDistance = 0;
static int leftDistance = 0;

float carController::getCarDistance()
{
    Serial.println(rightDistance);
    rightDistance += encoders.getCountsAndResetRight();
    leftDistance += encoders.getCountsAndResetLeft();
    Serial.println(rightDistance);
    leftDistance = leftDistance / 79;
    rightDistance = rightDistance / 79;
    float distance = (leftDistance + rightDistance) / 2;
    return distance;
}

float carController::calculatePowerConsumption(int distance)
{
    float powerConsumption = distance / carDrivingDistance;
    float batteryChargeLeft = 100 - powerConsumption;
    lcd.print(String(batteryChargeLeft));
    if (batteryChargeLeft <= 0)
    {
        motors.setSpeeds(0, 0);
    }
    return batteryChargeLeft;
}

float carController::calculateCarSpeed()
{
    float carSpeed = ((getCarDistance() / 100) / (millis() / 1000));
    return carSpeed;
}

void carController::updateDisplayInformation(String displayText, int displayTime)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(String(displayText));
    delay(displayTime);
}
