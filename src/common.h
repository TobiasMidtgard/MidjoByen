#pragma once
#define common_h
#include <Arduino.h>
#include <Zumo32U4.h>
#include <Wire.h>

// Converts method names from class to easily readable names.
static Zumo32U4ButtonA buttonA;
static Zumo32U4Motors motors;
static Zumo32U4Encoders encoders;
static Zumo32U4LCD lcd;
static Zumo32U4LineSensors lineSensor;
static Zumo32U4Buzzer buzzer;

// Driving distance in meters
static int carDrivingDistance = 10;
static float speedValue = 400;
