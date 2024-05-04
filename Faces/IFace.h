#pragma once

#include <Arduino.h>
#include "Rendering/Object.h"

class IFace {
public:
    virtual ~IFace() = default;

    virtual Object* getObject() const = 0;

    Vector2D getWiggle(float amplitude = 5.0f) {
        auto xPeriod = 5.3f / amplitude;
        auto yPeriod = 6.7f / amplitude;

        auto time = micros() / 1000000.0f;
        auto xTime = fmod(time, xPeriod);
        auto yTime = fmod(time, yPeriod);

        auto xWave = sinf(xTime / xPeriod * 2.0f * 3.14159f);
        auto yWave = sinf(yTime / yPeriod * 2.0f * 3.14159f);

        xWave = min(max(xWave, -2.0f), 2.0f);
        yWave = min(max(yWave, -2.0f), 2.0f);

        return Vector2D(xWave, yWave);
    }
};