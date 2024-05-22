#pragma once

#include "math.h"
#include "IGenerator.h"

class EaseOutGenerator : public IGenerator {
private:
    float start;
    float end;
    float step;
    float value;

public:
    EaseOutGenerator() : start(0.0f), end(1.0f), step(0.01f) {
        value = start;
    }

    EaseOutGenerator(float start, float end, float step) : start(start), end(end), step(step) {
        value = start;
    }

    void reset() override {
        value = start;
    }

    bool isCompleted() override {
        return value == end;
    }

    float next(unsigned long delta) override {
        float progress = (value - start) / (end - start);

        value += step * float(delta) / 30.0f;
        if (value > end) value = end;

        return sqrt(progress);
    }
};
