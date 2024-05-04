#pragma once

#include "IMaterial.h"

class SolidMaterial : public IMaterial {
private:
    unsigned color;

public:
    explicit SolidMaterial(unsigned color) : color(color) {};

    uint32_t getColor(const Vector3D &position, const Vector3D &normal, const Vector2D &uv) override;
};
