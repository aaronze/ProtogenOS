#pragma once

#include "SpiralGradient.h"

class RainbowSpiral : public IMaterial {
private:
    SpiralGradient* rainbowSpiral;

public:
    RainbowSpiral(float gradientPeriod = 1.0f, Vector2D spiralCenter = Vector2D(0.5f, 0.5f), float spirality = 1.0f, float rotationSpeed = 0.03f) {
        unsigned int colors[6] = {0xFF0000, 0xFFFF00, 0x00FF00, 0x00FFFF, 0x0000FF, 0xFF00FF};
        auto vectorList = std::vector<unsigned int> (colors, colors + 6);
        rainbowSpiral = new SpiralGradient(vectorList, gradientPeriod, spiralCenter, spirality, rotationSpeed);
    }

    ~RainbowSpiral() {
        delete rainbowSpiral;
    }

    uint32_t getColor(const Vector3D& position, const Vector3D& normal, const Vector2D& uv) override {
        return rainbowSpiral->getColor(position, normal, uv);
    }

    void update(unsigned long delta) override {
        rainbowSpiral->update(delta);
    }
};
