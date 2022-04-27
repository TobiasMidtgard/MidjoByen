#include "SW_Battery.h"
#include "common.h"

static float distanceLeft = 0;
static float distanceRight = 0;
static float maxSpeed = 0;
static int lastDistance = 0;
static float lastValue = 0;

static unsigned long deltaTime = 0;

float carController::getCarDistance()
{
    distanceLeft += float(encoders.getCountsAndResetLeft()) / 81;
    distanceRight += float(encoders.getCountsAndResetRight()) / 81;
    float avgDistance = (distanceLeft + distanceRight) / 2;
    return avgDistance;
}

float carController::calculatePowerConsumption(int currentPower, int dangerZone)
{
    float powerConsumption = (((getCarDistance() - lastDistance) * (1 + (calculateAverageCarSpeed()) / 5))) / carDrivingDistance;
    // Serial.println(powerConsumption);
    // Serial.println(currentPower);
    lastDistance = getCarDistance();
    float batteryChargeLeft = currentPower - powerConsumption;
    if (batteryChargeLeft <= dangerZone)
    {
        updateDisplayInformation(String(batteryChargeLeft));
    }

    return batteryChargeLeft;
}

float carController::calculateDeltaSpeed(float timeFrame)
{
    if (millis() - deltaTime >= timeFrame)
    {
        float deltaSpeed = (((getCarDistance()) - lastValue)) / ((timeFrame) / 1000);
        lastValue = getCarDistance();
        deltaTime = millis();
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
    float carSpeed = calculateDeltaSpeed(100);
    if (maxSpeed < carSpeed)
    {
        maxSpeed = carSpeed;
    }
    return maxSpeed;
}

float carController::calculateSpeedOverPercent(int percent, bool onlyWhenDriving)
{
    static unsigned long millisCompensation = 0;
    static float timeOverDelta = 0;
    static float drivingTime = 0;
    static float percentAboveSpeed = 0;

    int currentSpeed = (calculateDeltaSpeed(100));

    if ((calculateMaxCarSpeed() * (percent / 100)) < currentSpeed)
    {
        timeOverDelta += millis() - millisCompensation;
    }

    if (currentSpeed > 0)
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

void carController::updateDisplayInformation(String displayText)
{
    lcd.setCursor(0, 0);
    lcd.print(String(displayText));
}
