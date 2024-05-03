#pragma once

#include "Math/Vector2D.h"
#include "Math/Vector3D.h"

class Material {
public:
    virtual unsigned getColor(const Vector3D& position, const Vector3D& normal, const Vector2D& uv) = 0;
};
