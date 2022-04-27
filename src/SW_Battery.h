#pragma once
#define SW_Battery_h
#include "common.h"

//* Controls the car:
// Finds the distance between.
// Calculates the power consmuption of the car.
// Updates the car's display to show information.
class carController
{
public:

    /**
     * @brief Finds the distance the car has traversed with the help of the Zumo32u4's built in encoders.
     *
     * @return the average distance driven in meter.
     */
    float getCarDistance();

    /**
     * @brief Calculates the power consumption of the car.
     *
     * @param currentPower the current power of the car.
     * @param dangerZone When the user should be notified about the battery level.
     * @return Battery charge remaining in %.
     */
    float calculatePowerConsumption(int currentPower, int dangerZone);

    /**
     * @brief Calculates the average speed over a time frame.
     *
     * @param timeFrame the time frame of the calculation.
     * @return the average speed over the time frame.
     */
    float calculateDeltaSpeed(int timeFrame);

    /**
     * @brief Calculates the average speed of the car.
     *
     * @return the average speed of the car in m/s.
     */
    float calculateAverageCarSpeed();

    /**
     * @brief Calculates the maximum speed of the car.
     *
     * @return the maximum speed of the car in m/s.
     */
    float calculateMaxCarSpeed();

    /**
     * @brief Calculates how many seconds the car drives over a set percentage of max speed.
     *
     * @param percent The percentage of the driving distance.
     * @return time the car drove over the percent of maximum speed in seconds.
     */
    int calculateSpeedOverPercent(int percent);

    /**
     * @brief Updates the display with set information.
     *
     * @param String the displayed information.
     */
    void updateDisplayInformation(String displayText);
};