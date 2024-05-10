#pragma once

#include <cstdint>
#include "Math/Vector2D.h"
#include "Math/Vector3D.h"

class IMaterial {
public:
    virtual ~IMaterial() = default;

    virtual uint32_t getColor(const Vector3D& position, const Vector3D& normal, const Vector2D& uv) = 0;
    virtual void update(unsigned long delta) {}
};
