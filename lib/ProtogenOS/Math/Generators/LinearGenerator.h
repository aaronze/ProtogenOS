#pragma once

#include "IGenerator.h"

class LinearGenerator : public IGenerator {
private:
    float start;
    float end;
    float step;
    float value;

public:
    LinearGenerator() : start(0.0f), end(1.0f), step(0.01f) {
        value = start;
    }

    LinearGenerator(float start, float end, float step) : start(start), end(end), step(step) {
        value = start;
    }

    void reset() override {
        value = start;
    }

    bool isCompleted() override {
        return value == end;
    }

    float next(unsigned long delta) override {
        float val = value;

        value += step * float(delta) / 30.0f;
        if (step > 0 && value > end) value = end;
        if (step < 0 && value < end) value = end;

        return val;
    }
};
