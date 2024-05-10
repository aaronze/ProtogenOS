#include "BoopSensor.h"

Adafruit_APDS9960 BoopSensor::sensor = Adafruit_APDS9960();
uint8_t BoopSensor::threshold = 5;
uint8_t BoopSensor::error = 255;

bool BoopSensor::begin(uint8_t threshold) {
    BoopSensor::threshold = threshold;

    Wire.setClock(100000);
    Wire.begin();
    Wire.setSDA(18);
    Wire.setSCL(19);
    Wire.beginTransmission(0x39);
    error = Wire.endTransmission();
    if (error != 0) return false;

    auto success = sensor.begin();
    if (success) sensor.enableProximity(true);
    return success;
}

uint8_t BoopSensor::getError() {
    return error;
}

bool BoopSensor::isBooped() {
    if (error != 0) return false;

    auto proximity = getProximityValue();
    return proximity > threshold;
}

uint8_t BoopSensor::getProximityValue() {
    auto startTime = millis();
    auto proximity = sensor.readProximity();
    if (millis() - startTime > 100) reset();
    return proximity;
}

// Private

void BoopSensor::reset() {
    Wire.end();
    delay(10);
    Wire.begin();
}


