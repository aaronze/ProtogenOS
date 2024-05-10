#pragma once

#include <math.h>
#include <vector>
#include "IMaterial.h"

class LinearGradient : public IMaterial {
private:
    std::vector<unsigned int> colors;
    float gradientPeriod;
    float angle;

public:
    explicit LinearGradient(const std::vector<unsigned int>& colors, float gradientPeriod = 1.0f, float angle = 0.0f)
        : colors(colors), gradientPeriod(gradientPeriod), angle(angle) {}

    uint32_t getColor(const Vector3D& position, const Vector3D& normal, const Vector2D& uv) override {
        auto angleInRadians = angle * M_PI / 180.0f;
        auto pos = (position.x * cos(angleInRadians) + position.y * sin(angleInRadians)) / gradientPeriod;
        pos -= floor(pos);

        auto colorIndex = (unsigned int)(pos * colors.size());
        return colors[colorIndex % colors.size()];
    }
};
