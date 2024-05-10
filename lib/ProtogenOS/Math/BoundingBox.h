#pragma once

#include <math.h>
#include <algorithm>
#include "Vector3D.h"
#include "Transform.h"

class BoundingBox {
private:
    Transform* transform;
    Vector3D minCorner, maxCorner;

public:
    BoundingBox(const Vector3D &min, const Vector3D &max) : minCorner(min), maxCorner(max) {}

    bool intersects(const Vector3D &rayOrigin, const Vector3D &rayDirection) const {
        Vector3D a = transform->transform(minCorner);
        Vector3D b = transform->transform(maxCorner);

        float tmin, tmax;
        if (rayDirection.x != 0.0f) {
            tmin = (a.x - rayOrigin.x) / rayDirection.x;
            tmax = (b.x - rayOrigin.x) / rayDirection.x;
            if (tmin > tmax) std::swap(tmin, tmax);
        } else {
            tmin = -INFINITY;
            tmax = INFINITY;
        }

        float tymin, tymax;
        if (rayDirection.y != 0.0f) {
            tymin = (a.y - rayOrigin.y) / rayDirection.y;
            tymax = (b.y - rayOrigin.y) / rayDirection.y;
            if (tymin > tymax) std::swap(tymin, tymax);
        } else {
            tymin = -INFINITY;
            tymax = INFINITY;
        }

        if ((tmin > tymax) || (tymin > tmax)) return false;

        if (tymin > tmin) tmin = tymin;
        if (tymax < tmax) tmax = tymax;

        float tzmin, tzmax;
        if (rayDirection.z != 0.0f) {
            tzmin = (a.z - rayOrigin.z) / rayDirection.z;
            tzmax = (b.z - rayOrigin.z) / rayDirection.z;
            if (tzmin > tzmax) std::swap(tzmin, tzmax);
        } else {
            tzmin = -INFINITY;
            tzmax = INFINITY;
        }

        return !((tmin > tzmax) || (tzmin > tmax));
    }

    void applyTransform(Transform* transform) {
        this->transform = transform;
    }
};
