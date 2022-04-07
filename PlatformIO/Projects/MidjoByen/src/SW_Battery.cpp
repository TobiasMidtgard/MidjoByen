#include "SW_Battery.h"
#include "common.h"

static int distanceLeft = 0;
static int distanceRight = 0;

float carController::getCarDistance()
{
    distanceLeft += encoders.getCountsAndResetLeft() / 79;
    distanceRight += encoders.getCountsAndResetRight() / 79;
    float avgDistance = (distanceLeft + distanceRight) / 2;
    return avgDistance;
}

float carController::calculatePowerConsumption(float distance)
{
    float powerConsumption = distance / carDrivingDistance;
    float batteryChargeLeft = 100 - powerConsumption;
    return batteryChargeLeft;
}

float carController::calculateCarSpeed(int distance)
{
    float carSpeed = ((getCarDistance() / 100) / (millis() / 1000));
    return carSpeed;
}

void carController::updateDisplayInformation(String displayText)
{
    lcd.setCursor(0, 0);
    lcd.print(String(displayText));
}
