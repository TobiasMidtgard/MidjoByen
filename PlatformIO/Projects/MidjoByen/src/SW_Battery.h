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
    struct DistanceDriven
    {
        int leftDistance;
        int rightDistance;
    };
    // carController();

    /*
    Finds the distance the car has traversed.
    Finds the distance the car has travelled since the start.
     @returned  distance The traveled distance in cm.
    */
    float getCarDistance();

    //* Resets the motors encoders values.
    void resetCarDistance();

    //* This function finds the distance the car has moved:
    // By using steps and the known gearRatio of the car,
    // We can find the speed of the car in Cm per second.

    float calculatePowerConsumption(float distance);

    //* This function calculates the power consumption:
    // By using the speed of the car and the formula 10 + 2x,
    // where x is cm/s, the mA used is calculated.

    float calculateCarSpeed(int distance);

    void updateDisplayInformation(String displayText);

    //* This function updates the display with information about the car:
    // It takes in the information you want to display and shows it,
    // you can control the time of how long the text should be displayed.
};