// include the nesccessary libraries.
#include <Arduino.h>
#include <Zumo32U4.h>
#include <Wire.h>
#include "LineFollower.h"
#include "common.h"

// Method to start the car and display information during the startup process.
void LineFollower::startUpSequence()
{

    lineSensor.initFiveSensors();
    Serial.begin(9600);
    lineSensor.initFiveSensors();
    lcd.init();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press A Button");

    buttonA.waitForButton();
    lcd.clear();
    calibrate();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Calb");
    lcd.setCursor(0, 1);
    lcd.print("Done");
    delay(1000);
    buzzer.playFrequency(440, 500, 8);
    delay(1000);
    lcd.clear();
}

// The linefollower to follow a piece of tape.
void LineFollower::lineFollower(bool _left, bool _right)
{
    leftCorner = _left;
    rightCorner = _right;

    if (leftCorner == false && rightCorner == false)
    {
        pos = lineSensor.readLine(linesensorValues);
        error = pos - wantedValue;
        int speedDifference = (error * Kp) + Td * (error - lastError);
        int leftSpeed = 400 + speedDifference;
        leftSpeed = constrain(leftSpeed, 0, speedValue);
        int rightSpeed = 400 - speedDifference;
        rightSpeed = constrain(rightSpeed, 0, speedValue);
        motors.setSpeeds(leftSpeed, rightSpeed);
    }

    else if (leftCorner == true || rightCorner == true)
    {
        motors.setSpeeds(200, 200);
    }

    else if (noRoad == 1)
    {
        motors.setSpeeds(0, 100);
    }
}

void LineFollower::calibrate()
{
    delay(1000);
    for (int i = 0; i <= 120; i++)
    {
        if (i > 30 && i <= 90)
        {
            motors.setSpeeds(-150, 150);
        }
        else
        {
            motors.setSpeeds(150, -150);
        }
        lineSensor.calibrate();
    }
    motors.setSpeeds(0, 0);
    lineSensor.readCalibrated(linesensorValues);
}

void LineFollower::turnAngle(int angle, int turnSpeed, bool turnWithBothWheels)
{
    // turn the robot by angle degrees
    int leftStartAngle = encoders.getCountsLeft();
    int rightStartAngle = encoders.getCountsRight();

    motors.setSpeeds(0, 0);
    delay(250);

    if (turnWithBothWheels == true)
    {
        negativeTurnSpeed = -turnSpeed;
        turnRefrence = 7.5;
    }
    else
    {
        negativeTurnSpeed = 0;
        turnRefrence = 14.5;
    }

    if (angle > 0)
    {
        while (angle > (encoders.getCountsLeft() - leftStartAngle) / turnRefrence)
        {
            motors.setSpeeds(turnSpeed, negativeTurnSpeed);
        }
    }
    else if (angle < 0)
    {
        while (abs(angle) > (encoders.getCountsRight() - rightStartAngle) / turnRefrence)
        {
            motors.setSpeeds(negativeTurnSpeed, turnSpeed);
        }
    }
    motors.setSpeeds(0, 0);
}

bool LineFollower::checkForTurn(int firstValue, int secondValue, int thirdValue)
{
    // Checks if the car drives over a sharp turn
    if (linesensorValues[firstValue] >= 900 && linesensorValues[2] >= 900 && linesensorValues[secondValue] >= 900 && leftCorner == false && linesensorValues[thirdValue] > 200)
    {
        cornerTime = millis();
        deadEnd = 1;
        deadTime = millis();
        return true;
    }
    return false;
}

void LineFollower::endOfLine()
{
    if (linesensorValues[0] < 200 && linesensorValues[1] < 200 && linesensorValues[2] < 200 && linesensorValues[3] < 200 && linesensorValues[4] < 200)
    {
        if (deadEnd == 0)
        {
            motors.setSpeeds(200, 200);
        }
        else if (deadEnd == 1)
        {
            turnAngle(180, 200, true);
        }
    }

    if ((millis() - cornerTime) > 100 && (millis() - cornerTime) < 200)
    {
        if (linesensorValues[2] <= 200)
        {
            lcd.setCursor(0, 0);
            turnTime = millis();
            noRoad = 1;
            lcd.print(noRoad);
        }
        leftCorner = false;
        rightCorner = false;
    }

    if ((millis() - turnTime) >= 500)
    {
        noRoad = 0;
    }

    if ((millis() - deadTime) >= 1000)
    {
        deadEnd = 0;
    }

    lastError = error;
}
