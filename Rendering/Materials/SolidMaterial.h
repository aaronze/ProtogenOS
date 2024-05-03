#pragma once

#include "Material.h"

class SolidMaterial : public Material {
private:
    unsigned color;

public:
    explicit SolidMaterial(unsigned color) : color(color) {};

    unsigned int getColor(const Vector3D &position, const Vector3D &normal, const Vector2D &uv) override;
};
