#pragma once

#include "Vector3D.h"

class Quaternion {
public:
    float w, x, y, z;

    Quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f) : w(w), x(x), y(y), z(z) {}

    static Quaternion createRotationQuaternion(const float angle, const Vector3D axis);

    Vector3D rotate(const Vector3D& vector) const;
};
