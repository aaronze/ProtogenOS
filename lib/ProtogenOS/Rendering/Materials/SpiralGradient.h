#pragma once

#include <math.h>
#include <vector>
#include "IMaterial.h"

class SpiralGradient : public IMaterial {
private:
    std::vector<unsigned int> colors;
    float gradientPeriod;
    Vector2D spiralCenter;
    float spirality;
    float angle;
    float rotationSpeed;

public:
    SpiralGradient(
        const std::vector<unsigned int>& colors,
        float gradientPeriod = 1.0f,
        Vector2D spiralCenter = Vector2D(0.5f, 0.5f),
        float spirality = 1.0f,
        float rotationSpeed = 0.01f)
        : colors(colors), gradientPeriod(gradientPeriod), spiralCenter(spiralCenter), spirality(spirality), rotationSpeed(rotationSpeed) {}

    uint32_t getColor(const Vector3D& position, const Vector3D& normal, const Vector2D& uv) override {
        float dx = position.x - spiralCenter.x;
        float dy = position.y - spiralCenter.y;

        double r = sqrt(dx*dx + dy*dy);
        double theta = atan2(dy, dx);

        float pos = (r + spirality * theta) / gradientPeriod + angle;
        pos -= floor(pos);
        unsigned int colorIndex = pos * colors.size();
        return colors[colorIndex % colors.size()];
    }

    void update(unsigned long delta) override {
        angle += rotationSpeed * float(delta) / 30.0f;
    }
};
