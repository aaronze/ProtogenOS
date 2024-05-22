#pragma once

#include "math.h"
#include "IGenerator.h"

class ElasticOutGenerator : public IGenerator {
private:
    float start;
    float end;
    float step;
    float value;

public:
    ElasticOutGenerator() : start(0.0f), end(1.0f), step(0.01f) {
        value = start;
    }

    ElasticOutGenerator(float start, float end, float step) : start(start), end(end), step(step) {
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
        const float springy = 0.5f;

        value += step * float(delta) / 30.0f;
        if (value > end) value = end;

        return powf(2, -10*progress) * sinf((progress-springy/4) * (2*M_PI)/springy) + 1.0f;
    }
};
