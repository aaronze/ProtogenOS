#pragma once

#include <Arduino.h>

class ButtonHandler {
private:
    bool previousState;
    long previousMillis;
    short inputCount;
    short inputStream[4];
    short pin;
    short currentValue;

public:
    explicit ButtonHandler(short pin);

    bool update();
    short getCurrentValue();
};
