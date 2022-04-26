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
  // create necessary variables
  int pos;
  unsigned int linesensorValues[5];
  int error;
  const int wantedValue = 2000;
  float Kp = 0.6;
  float Td = 2;
  int lastError = 0;
  int leftCorner = 0;
  int rightCorner = 0;
  int cornerTime = 0;
  int turnTime = 0;
  int noRoadLeft = 0;
  int noRoadRight = 0;
  int deadEnd = 0;
  int deadTime = 0;
  int rightNext = 0;
  int negativeTurnSpeed;
  int turnRefrence;
  int afterNext = 0;
  int afterTime = 0;

  /**
   * @brief initializes the car.
   *
   */
  void init();

  /**
   * @brief Checks if the car sees a turn in either direction.
   *
   * @param firstValue the first sensor to check.
   * @param secondValue the second sensor to check.
   * @param thirdValue the third sensor to check.
   * @return if there is a turn.
   */
  bool checkForTurn(int firstValue, int secondValue, int thirdValue);

  /**
   * @brief turns the car to a set angle in either direction.
   *
   * @param angle Chooses the angle the car should turn to. Positive number is right turn, negative number is left turn.
   * @param turnSpeed The speed the car should turn at.
   * @param turnWithBothWheels If the car should turn with both wheels or just one.
   */
  void turnAngle(int angle, int turnSpeed, bool turnWithBothWheels);

  /**
   * @brief Follows a line of tape with a PID controller.
   *
   */
  void lineFollower();

  /**
   * @brief Checks if the car reached a dead end.
   *
   */
  void endOfLine();

  /**
   * @brief Calibrates the car's line sensors.
   *
   */
  void calibrate();
};