#pragma once
#define LineFollower_h
#include <Arduino.h>

/*
    The class controls the movement of the car.
    The car gets calibrated, has a linefollower,
    corner detection and dead end detection.
*/

class LineFollower
{
public:
  int pos;
  unsigned int linesensorValues[5];
  int error;
  const int wantedValue = 2000;
  float Kp = 0.8;
  float Td = 1.5;
  int lastError = 0;

  bool leftCorner = false;
  bool rightCorner = false;
  int cornerTime = 0;
  int turnTime = 0;
  int noRoad = 0;
  int deadEnd = 0;
  int deadTime = 0;

  int negativeTurnSpeed;
  int turnRefrence;

  /*
      Runs during startup to start the car and display information about the process.
  */
  void startUpSequence();
  /*
  Checks if the car should turn by reading the sensor values of the different sensors on the car.

  @param firstValue The adress of the first sensor to check.
  @param secondValue The second adress of the sensor to check.
  @param thirdValue The third adress of the sensor to check.
  @return If the car should turn or not.
  */
  bool checkForTurn(int firstValue, int secondValue, int thirdValue);
  /*
  Turns the car as many degrees as wanted, direction and speed is adjustable.

  @param angle How many degrees the car should turn.
  @param speed How fast the car should turn.
  @param turnWithBothWheels If the car should turn with both wheels or not.
  @return nothing.
  */
  void turnAngle(int angle, int turnSpeed, bool turnWithBothWheels);
  /*
  Controls the car and follows a line of tape.

  @param cornerLeft if there is a corner on the left.
  @param cornerRight if there is a corner on the right.
  @return nothing.

  */
  void lineFollower(bool _left, bool _right);
  /*
    Checks if the car has reached a dead end.
    @return nothing.
  */
  void endOfLine();
  /*
    Calibrates the sensors on the car
    @return nothing.
  */
  void calibrate();
};