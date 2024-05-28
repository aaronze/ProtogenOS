#pragma once

#include <cmath>
#include <algorithm>
#include "Vector3D.h"
#include "Transform.h"

class BoundingBox {
private:
    Vector3D minCorner, maxCorner;
    Vector3D curMinCorner, curMaxCorner;

public:
    BoundingBox() = default;
    BoundingBox(const Vector3D& min, const Vector3D& max) : minCorner(min), maxCorner(max), curMinCorner(min), curMaxCorner(max) {}

    const Vector3D& min() const {
        return curMinCorner;
    }

    const Vector3D& max() const {
        return curMaxCorner;
    }

    bool intersects(const Vector3D& rayOrigin, const Vector3D& rayDirection) const {
        float tmin = (curMinCorner.x - rayOrigin.x) / rayDirection.x;
        float tmax = (curMaxCorner.x - rayOrigin.x) / rayDirection.x;
        if (tmin > tmax) std::swap(tmin, tmax);

        float tymin = (curMinCorner.y - rayOrigin.y) / rayDirection.y;
        float tymax = (curMaxCorner.y - rayOrigin.y) / rayDirection.y;
        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax)) return false;

        if (tymin > tmin) tmin = tymin;
        if (tymax < tmax) tmax = tymax;

        float tzmin = (curMinCorner.z - rayOrigin.z) / rayDirection.z;
        float tzmax = (curMaxCorner.z - rayOrigin.z) / rayDirection.z;
        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        return !((tmin > tzmax) || (tzmin > tmax));
    }

    void applyTransform(const Transform& transform) {
        curMinCorner = transform.transform(minCorner);
        curMaxCorner = transform.transform(maxCorner);
    }
};
