#pragma once

#include <Arduino.h>

class IEffect {
private:
    unsigned long stopTime;

public:
    explicit IEffect(unsigned long duration) {
        stopTime = millis() + duration;
    }
    virtual ~IEffect() = default;

    bool isAlive() const {
        return millis() <= stopTime;
    }

    virtual void update(unsigned long delta) = 0;
};
