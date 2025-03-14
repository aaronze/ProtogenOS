#pragma once

#include <math.h>
#include <vector>

template<size_t window>
class MinSlidingWindowFilter {
private:
    const int minWindow = window / 10;
    float values[window];
    float minValues[window / 10];
    bool isFilled = false;
    int fillIndex = 0;
    int minIndex = 0;

    void pushValue(float value) {
        values[fillIndex++] = value;
        if (fillIndex >= window) {
            isFilled = true;
            fillIndex %= window;
        }
    }

    void pushMinValue(float minValue) {
        minValues[minIndex++] = minValue;
        if (minIndex >= minWindow) {
            minIndex %= minWindow;
        }
    }

    float getMin() {
        auto min = values[0];
        auto filled = isFilled ? window : fillIndex;
        for (int i = 1; i < filled; i++) {
            if (values[i] < min) min = values[i];
        }
        return min;
    }

    float getMinAverage() {
        float average = 0;
        for (int i = 0; i < minWindow; i++) {
            average += minValues[i];
        }
        return average / minWindow;
    }

public:
    MinSlidingWindowFilter() {
        for (int i = 0; i < window; i++) {
            values[i] = 0.0f;
        }
        for (int i = 0; i < minWindow; i++) {
            minValues[i] = 0.0f;
        }
    }

    float filterValues(std::vector<float>& values) {
        for (int i = 0; i < values.size(); i++) {
            filter(values[i]);
        }
        return getMinAverage();
    }

    float filter(float value) {
        pushValue(value);
        pushMinValue(getMin());
        return getMinAverage();
    }
};