#pragma once

#include <math.h>
#include <memory>
#include <vector>
#include "IMaterial.h"
#include "ExternalDevices/Sensors/Microphone.h"
#include "Math/Filters/HighPassFilter.h"
#include "Math/Filters/MinSlidingWindowFilter.h"
#include "Math/Filters/MaxSlidingWindowFilter.h"

class Oscilloscope : public IMaterial {
private:
    std::shared_ptr<Microphone> microphone;
    std::vector<float> frequencies;
    std::vector<float> window = std::vector<float>(16);

    MinSlidingWindowFilter<40> minFilter = MinSlidingWindowFilter<40>();
    MaxSlidingWindowFilter<40> maxFilter = MaxSlidingWindowFilter<40>();
    HighPassFilter highPassFilter = HighPassFilter(4000.0f, 44100);

    float minValue;
    float maxValue;
    float midValue;

public:
    explicit Oscilloscope(std::shared_ptr<Microphone>& microphone) : microphone(microphone) {}

    void update(unsigned long delta) override {
        microphone->update();
        frequencies = microphone->getFrequencies();

        float average = 0.0f;
        for (int i = 0; i < frequencies.size(); i++) average += frequencies[i];
        average /= frequencies.size();

        highPassFilter.filter(frequencies, average);

        minValue = minFilter.filterValues(frequencies);
        maxValue = maxFilter.filterValues(frequencies);

        for (int i = 0; i < window.size(); i++) {
            window[i] = 0;
        }
        for (int i = 0; i < frequencies.size(); i++) {
            window[map(i, 0, frequencies.size(), 0, window.size())] += frequencies[i];
        }
        for (int i = 0; i < window.size(); i++) {
            window[i] /= (frequencies.size() / window.size());
        }
    }

    uint32_t getColor(const Vector3D& position, const Vector3D& normal, const Vector2D& uv) override {
        float x = map(position.x, -1.0f, 1.0f, 0.0f, window.size());
        float y = map(position.y, -1.0f, 1.0f, 0.0f, 32.0f);

        auto value = window[floor(x)];
        auto value2 = window[x < window.size() - 1.0f ? ceil(x) : floor(x)];
        auto leftX = map(floor(x), 0.0f, window.size(), -1.0f, 1.0f);
        auto rightX = map(ceil(x), 0.0f, window.size(), -1.0f, 1.0f);
        auto ratio = map(position.x, leftX, rightX, 0.0f, 1.0f);

        auto firstPoint = map(value, minValue, 50.0f, 0.0f, 32.0f);
        auto secondPoint = map(value2, minValue, 50.0f, 0.0f, 32.0f);

        auto height = firstPoint * (1.0f - ratio) + secondPoint * ratio;

        if (y < height) return 0xFF0000;

        return 0x000000;
    }
};
