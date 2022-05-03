#include "SW_Battery.h"
#include "common.h"

static float distanceLeft = 0;
static float distanceRight = 0;
static float maxSpeed = 0;
static float lastDistance = 0;
static float lastValue = 0;

static float deltaTime = 0;

float SWBattery::getCarDistance()
{
    distanceLeft += float(encoders.getCountsAndResetLeft()) / 81;
    distanceRight += float(encoders.getCountsAndResetRight()) / 81;
    float avgDistance = (distanceLeft + distanceRight) / 2;

    return avgDistance;
}

float SWBattery::calculatePowerConsumption(int dangerZone)
{
    static float batteryChargeLeft = 100;
    float currentDistance = getCarDistance();
    float powerConsumption = ((currentDistance - lastDistance) / carDrivingDistance);
    lastDistance = currentDistance;
    batteryChargeLeft = batteryChargeLeft - powerConsumption;
    if (batteryChargeLeft <= dangerZone)
    {
        updateDisplayInformation(String(batteryChargeLeft));
    }

    return batteryChargeLeft;
}

float SWBattery::calculateDeltaSpeed(float timeFrame)
{

    float millisAsFloat = millis();
    if (millis() - deltaTime >= timeFrame)
    {
        deltaSpeed = (((getCarDistance()) - lastValue)) / ((millisAsFloat - deltaTime) / 1000);
        lastValue = getCarDistance();
        deltaTime = millis();
        return deltaSpeed;
    }
}

float SWBattery::calculateAverageCarSpeed(bool onlyWhenDriving)
{
    static float millisCompensation = millis() - 1000;
    static float drivingTime = 0;
    static float carSpeed = 0;

    if (deltaSpeed > 0)
    {
        drivingTime += millis() - millisCompensation;
    }

    millisCompensation = millis();

    if (onlyWhenDriving)
    {
        carSpeed = (getCarDistance() / (drivingTime / 1000));
    }

    else if (!onlyWhenDriving)
    {
        float runTime = millis() / 1000;
        carSpeed = (getCarDistance() / (runTime));
    }

    return carSpeed;
}

float SWBattery::calculateMaxCarSpeed()
{
    if (maxSpeed < deltaSpeed)
    {
        maxSpeed = deltaSpeed;
    }
    return maxSpeed;
}

float SWBattery::calculateSpeedOverPercent(float percent, bool onlyWhenDriving)
{
    static unsigned long millisCompensation = millis();
    static float timeOverDelta = 0;
    static float drivingTime = 0;
    static float percentAboveSpeed = 0;

    if ((calculateMaxCarSpeed() * (percent / 100)) < deltaSpeed)
    {
        timeOverDelta += millis() - millisCompensation;
    }

    if (deltaSpeed > 0)
    {
        drivingTime += millis() - millisCompensation;
    }
    millisCompensation = millis();

    if (onlyWhenDriving)
    {
        percentAboveSpeed = ((timeOverDelta / drivingTime) * 100);
    }
    else if (!onlyWhenDriving)
    {
        percentAboveSpeed = ((timeOverDelta / millisCompensation) * 100);
    }

    return percentAboveSpeed;
}

void SWBattery::updateDisplayInformation(String displayText)
{
    lcd.setCursor(0, 0);
    lcd.print(String(displayText));
}
