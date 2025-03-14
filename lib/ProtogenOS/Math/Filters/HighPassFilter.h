#pragma once

#include <math.h>
#include <vector>

class HighPassFilter {
private:
    float cutoffFrequency;
    float samplingRate;

public:
    HighPassFilter(float cutoffFrequency, float samplingRate) : cutoffFrequency(cutoffFrequency), samplingRate(samplingRate) {}

    void filter(std::vector<float>& values, float minimumValue = 0.0f) {
        auto bins = values.size();
        auto cutoffIndex = std::round(cutoffFrequency * bins / samplingRate);

        for (int i = 0; i < cutoffIndex; i++) {
            values[i] = minimumValue;
        }
    }
};