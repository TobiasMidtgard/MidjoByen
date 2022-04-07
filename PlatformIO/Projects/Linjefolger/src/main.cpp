/*
  This program controls the Zumo32U4's movement.
  The car follows a predetermined tape line and can comprehend small gaps in the tape.
  If the gap is to big, the car will know it is a dead end and turn back.
*/

// Imports needed libraries
#include <Arduino.h>
#include <Zumo32U4.h>
#include <Wire.h>

// Defines complicated variable names to shorter more usable names.
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;
Zumo32U4Encoders encoders;
Zumo32U4LCD lcd;
Zumo32U4LineSensors lineSensor;
Zumo32U4Buzzer buzzer;

// The deviation off the line.
int pos;

// Array to hold the values of the line sensors.
unsigned int linesensorValues[5];

// The allowed deviation from the line.
int error;

// The preffered value of the line sensors, used to determine if the car is on the line.
const int wantedValue = 2000;

// PD controller variables.
float Kp = 0.8;
float Td = 1.5;

// Minimizes the overshoot of the correction.
int lastError = 0;

// The program counter for the wait function.
unsigned long time77 = 0;

// Initializes the calibration function.
void calibrate();

// Function: setup() runs once, when the device is first turned on.
void setup()
{

  lineSensor.initFiveSensors();
  Serial.begin(9600);
  lineSensor.initFiveSensors();
  lcd.init();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press A Button");
  calibrate();
  buttonA.waitForButton();
  lcd.clear();
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Calb");
  lcd.setCursor(0, 1);
  lcd.print("Done");
  delay(1000);
  buzzer.playFrequency(440, 500, 8);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Currently");
  lcd.setCursor(0, 1);
  lcd.print("driving");
}

// Function: loop() runs until the program is stopped.
void loop()
{

  // waits 10 milliseconds, without impeading code below.
  if ((millis() - time77) > 10)
  {
    // Reads and prints out the sensor values of all 5 line sensors.
    time77 = millis();
    lineSensor.readCalibrated(linesensorValues);
    Serial.print(linesensorValues[0]);
    Serial.print(" ");
    Serial.print(linesensorValues[1]);
    Serial.print(" ");
    Serial.print(linesensorValues[2]);
    Serial.print(" ");
    Serial.print(linesensorValues[3]);
    Serial.print(" ");
    Serial.print(linesensorValues[4]);
    Serial.println(" ");
  }

  // Reads the sensor values of all 5 line sensors.
  pos = lineSensor.readLine(linesensorValues);
  // Finds the deviation from the line.
  error = pos - wantedValue;
  // Determins the difference in speed between the two wheels.
  int speedDifference = (error * Kp) + Td * (error - lastError);
  // creates a value for the speed for the left and right wheel.
  int leftSpeed = 400 + speedDifference;
  leftSpeed = constrain(leftSpeed, 0, 30);
  int rightSpeed = 400 - speedDifference;
  rightSpeed = constrain(rightSpeed, 0, 30);
  // Sets the speed of the left and right wheels.
  motors.setSpeeds(leftSpeed, rightSpeed);
  // Sets the last error to the current error.
  lastError = error;
}

// Function: cal() calibrates the line sensors.
// Description: This function calibrates the car,
// by turning the car 90 degrees, then 180 degrees and then 90 degrees.
void calibrate()
{
  delay(1000);
  // uses a for loop to change the rotation of the car.
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
}