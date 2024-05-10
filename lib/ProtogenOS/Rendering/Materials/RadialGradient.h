#pragma once

#include <math.h>
#include <vector>
#include "IMaterial.h"

class RadialGradient : public IMaterial {
private:
    std::vector<unsigned int> colors;
    float gradientPeriod;
    Vector2D radialCenter;

public:
    explicit RadialGradient(
        const std::vector<unsigned int>& colors,
        float gradientPeriod = 1.0f,
        Vector2D radialCenter = Vector2D(0.5f, 0.5f))
        : colors(colors), gradientPeriod(gradientPeriod), radialCenter(radialCenter) {}

    uint32_t getColor(const Vector3D& position, const Vector3D& normal, const Vector2D& uv) override {
        float distance = (position.xy() - radialCenter).length();
        float angle = atan2(position.y - radialCenter.y, position.x - radialCenter.x);
        float colorIndex = angle / (2 * M_PI) * gradientPeriod + distance / gradientPeriod * colors.size();
        colorIndex = fmod(colorIndex, colors.size());
        return colors[colorIndex];
    }
};
