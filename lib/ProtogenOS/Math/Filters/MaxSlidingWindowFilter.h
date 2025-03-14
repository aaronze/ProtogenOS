#pragma once

#include <math.h>
#include <vector>

template<size_t window>
class MaxSlidingWindowFilter {
private:
    const int maxWindow = window / 10;
    float values[window];
    float maxValues[window / 10];
    bool isFilled = false;
    int fillIndex = 0;
    int maxIndex = 0;

    void pushValue(float value) {
        values[fillIndex++] = value;
        if (fillIndex >= window) {
            isFilled = true;
            fillIndex %= window;
        }
    }

    void pushMaxValue(float maxValue) {
        maxValues[maxIndex++] = maxValue;
        if (maxIndex >= maxWindow) {
            maxIndex %= maxWindow;
        }
    }

    float getMax() {
        auto max = values[0];
        auto filled = isFilled ? window : fillIndex;
        for (int i = 1; i < filled; i++) {
            if (values[i] > max) max = values[i];
        }
        return max;
    }

    float getMaxAverage() {
        float average = 0;
        for (int i = 0; i < maxWindow; i++) {
            average += maxValues[i];
        }
        return average / maxWindow;
    }

public:
    MaxSlidingWindowFilter() {
        for (int i = 0; i < window; i++) {
            values[i] = 0.0f;
        }
        for (int i = 0; i < maxWindow; i++) {
            maxValues[i] = 0.0f;
        }
    }

    float filterValues(std::vector<float>& values) {
        for (int i = 0; i < values.size(); i++) {
            filter(values[i]);
        }
        return getMaxAverage();
    }

    float filter(float value) {
        pushValue(value);
        pushMaxValue(getMax());
        return getMaxAverage();
    }
};