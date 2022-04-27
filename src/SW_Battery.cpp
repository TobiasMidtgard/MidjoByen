#include "SW_Battery.h"
#include "common.h"

static int distanceLeft = 0;
static int distanceRight = 0;
static int maxSpeed = 0;
static int lastDistance = 0;

static unsigned long deltaTime = 0;

float carController::getCarDistance()
{
    distanceLeft += encoders.getCountsAndResetLeft() / 79;
    distanceRight += encoders.getCountsAndResetRight() / 79;
    float avgDistance = (distanceLeft + distanceRight) / 2;
    return avgDistance;
}

float carController::calculatePowerConsumption(int currentPower, int dangerZone)
{
    float powerConsumption = ((getCarDistance() - lastDistance) * (1 + (calculateAverageCarSpeed()) / 5)) / carDrivingDistance;
    lastDistance = getCarDistance();
    float batteryChargeLeft = currentPower - powerConsumption;
    if (batteryChargeLeft <= dangerZone)
    {
        updateDisplayInformation(String(batteryChargeLeft));
    }

    return batteryChargeLeft;
}

float carController::calculateDeltaSpeed(int timeFrame)
{
    if (millis() - deltaTime >= timeFrame)
    {
        deltaTime = millis();
        float deltaSpeed = (distanceLeft - distanceRight) / timeFrame;
        return deltaSpeed;
    }
}

float carController::calculateAverageCarSpeed()
{
    float carSpeed = ((getCarDistance() / 100) / (millis() / 1000));
    return carSpeed;
}

float carController::calculateMaxCarSpeed()
{
    float carSpeed = calculateDeltaSpeed(1000);
    if (maxSpeed < carSpeed)
    {
        maxSpeed = carSpeed;
    }
    return maxSpeed;
}

int carController::calculateSpeedOverPercent(int percent)
{
    int timeOverDelta = 0;
    for (int time = 0; time >= 60; time++)
    {
        if (calculateMaxCarSpeed() < calculateDeltaSpeed(1000) * (percent / 100))
        {
            timeOverDelta++;
        }
    }
}

void carController::updateDisplayInformation(String displayText)
{
    lcd.setCursor(0, 0);
    lcd.print(String(displayText));
}
