#pragma once

#include "Vector2D.h"
#include "Vector3D.h"

class Triangle {
public:
    Vector3D v1;
    Vector3D v2;
    Vector3D v3;

    Vector2D uv1;
    Vector2D uv2;
    Vector2D uv3;

    Vector3D edge1;
    Vector3D edge2;

    Triangle(Vector3D v1, Vector3D v2, Vector3D v3);

    bool intersects(Vector3D rayOrigin, Vector3D rayDirection, Vector3D* outIntersection, Vector2D* outColor);
};
