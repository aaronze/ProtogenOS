#include "Triangle.h"

#define EPSILON 0.0000001

Triangle::Triangle(Vector3D v1, Vector3D v2, Vector3D v3) {
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    this->uv1 = {0, 0};
    this->uv2 = {1, 0};
    this->uv3 = {0, 1};

    this->edge1 = v2 - v1;
    this->edge2 = v3 - v1;
    this->normal = edge1.cross(edge2).normalize();
}

bool Triangle::intersects(Vector3D rayOrigin, Vector3D rayDirection, Vector3D *outIntersection, Vector2D *outColor) {
    Vector3D h = rayDirection.cross(edge2);
    float a = edge1.dot(h);
    if (a > -EPSILON && a < EPSILON) return false; // Parallel

    float f = 1.0f / a;
    Vector3D s = rayOrigin - v1;
    float u = f * s.dot(h);
    if (u < 0.0f || u > 1.0f) return false;

    Vector3D q = s.cross(edge1);
    float v = f * rayDirection.dot(q);
    if (v < 0.0f || u + v > 1.0f) return false;

    float t = f * edge2.dot(q);
    if (t > EPSILON) {
        *outIntersection = rayOrigin + rayDirection * t;
        *outColor = uv1 + (uv2 - uv1) * u + (uv3 - uv1) * v;
        return true;
    }

    return false;
}