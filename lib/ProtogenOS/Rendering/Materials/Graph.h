#pragma once

#include <math.h>
#include <vector>
#include "IMaterial.h"

class Graph : public IMaterial {
private:
    std::vector<float> values;

public:
    explicit Graph(std::vector<float>& values) : values(values) {}

    void setValues(std::vector<float>& values) {
        this->values = values;
    }

    uint32_t getColor(const Vector3D& position, const Vector3D& normal, const Vector2D& uv) override {
        float x = (position.x + 1.0f) / 2.0f;
        float y = (position.y + 1.0f) / 2.0f;

        auto value = values[x * values.size()];
        if (y < value / 255.0f) return 0xFF0000;

        return 0x000000;
    }
};
