#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_APDS9960.h>

// APDS9960
class BoopSensor {
private:
    static Adafruit_APDS9960 sensor;
    static uint8_t threshold;
    static uint8_t error;

    static void reset();

public:
    static bool begin(uint8_t threshold);
    static uint8_t getError();
    static bool isBooped();
    static uint8_t getProximityValue();
};
