#pragma once

#include <Arduino.h>
#include "IInput.h"

class ButtonHandler : public IInput {
private:
    bool previousState;
    long previousMillis;
    short inputCount;
    short inputStream[4]{};
    unsigned short pin;
    short currentValue;

public:
    explicit ButtonHandler(unsigned short pin);

    bool update() override;
    short getCurrentValue() override;
};
