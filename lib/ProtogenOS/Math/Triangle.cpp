#include "Triangle.h"

#define EPSILON 0.0000001

Triangle::Triangle(Vector3D* v1, Vector3D* v2, Vector3D* v3) {
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    this->uv1 = {0, 0};
    this->uv2 = {1, 0};
    this->uv3 = {0, 1};
}

bool Triangle::intersects(const Vector3D& rayOrigin, const Vector3D& rayDirection, Vector3D* outIntersection, Vector2D* outColor) const {
    float edge1X = v2->x - v1->x;
    float edge1Y = v2->y - v1->y;
    float edge1Z = v2->z - v1->z;

    float edge2X = v3->x - v1->x;
    float edge2Y = v3->y - v1->y;
    float edge2Z = v3->z - v1->z;

    float hX = rayDirection.y * edge2Z - rayDirection.z * edge2Y;
    float hY = rayDirection.z * edge2X - rayDirection.x * edge2Z;
    float hZ = rayDirection.x * edge2Y - rayDirection.y * edge2X;

    float a = edge1X * hX + edge1Y * hY + edge1Z * hZ;
    if (a > -EPSILON && a < EPSILON) return false;

    float f = 1.0f / a;
    float sX = rayOrigin.x - v1->x;
    float sY = rayOrigin.y - v1->y;
    float sZ = rayOrigin.z - v1->z;

    float u = f * (sX * hX + sY * hY + sZ * hZ);
    if (u < 0.0 || u > 1.0) return false;

    float qX = sY * edge1Z - sZ * edge1Y;
    float qY = sZ * edge1X - sX * edge1Z;
    float qZ = sX * edge1Y - sY * edge1X;

    float v = f * (rayDirection.x * qX + rayDirection.y * qY + rayDirection.z * qZ);
    if (v < 0.0 || u + v > 1.0) return false;

    float t = f * (edge2X * qX + edge2Y * qY + edge2Z * qZ);
    if (t > EPSILON) {
        outIntersection->x = rayOrigin.x + rayDirection.x * t;
        outIntersection->y = rayOrigin.y + rayDirection.y * t;
        outIntersection->z = rayOrigin.z + rayDirection.z * t;
        outColor->x = uv1.x + (uv2.x - uv1.x) * u + (uv3.x - uv1.x) * v;
        outColor->y = uv1.y + (uv2.y - uv1.y) * u + (uv3.y - uv1.y) * v;
        return true;
    }

    return false;
}
