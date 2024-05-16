#pragma once

#include "math.h"
#include "IGenerator.h"

class SineGenerator : public IGenerator {
private:
    float start;
    float amplitude;
    float frequency;
    float value;

public:
    SineGenerator() : start(0.0f), amplitude(1.0f), frequency(1.0f) {
        value = start;
    }

    SineGenerator(float start, float amplitude, float frequency) : start(start), amplitude(amplitude), frequency(frequency) {
        value = start;
    }

    void reset() override {
        value = start;
    }

    bool isCompleted() override {
        return false;
    }

    float next(unsigned long delta) override {
        float progress = (value - start);
        value += M_PI / frequency * float(delta) / 1000.0f;
        return sinf(progress) * amplitude * 2.0f - 1.0f;
    }
};
