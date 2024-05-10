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

        float tmin = (a.x - rayOrigin.x) / rayDirection.x;
        float tmax = (b.x - rayOrigin.x) / rayDirection.x;
        if (tmin > tmax) std::swap(tmin, tmax);

        float tymin = (a.y - rayOrigin.y) / rayDirection.y;
        float tymax = (b.y - rayOrigin.y) / rayDirection.y;
        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax)) return false;

        if (tymin > tmin) tmin = tymin;
        if (tymax < tmax) tmax = tymax;

        float tzmin = (a.z - rayOrigin.z) / rayDirection.z;
        float tzmax = (b.z - rayOrigin.z) / rayDirection.z;
        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        return !((tmin > tzmax) || (tzmin > tmax));
    }

    void applyTransform(Transform* transform) {
        this->transform = transform;
    }
};
