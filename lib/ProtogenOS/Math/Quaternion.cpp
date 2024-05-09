#include "Quaternion.h"

#include <math.h>

Quaternion Quaternion::createRotationQuaternion(const float angleInDegrees, const Vector3D axis) {
    float angleInRadians = (angleInDegrees / 180.0f) * 3.14159f;
    float s = sinf(angleInRadians / 2.0f);
    Quaternion result(cosf(angleInRadians / 2.0f), axis.x * s, axis.y * s, axis.z * s);
    result.normalize();
    return result;
}

void Quaternion::normalize() {
    float len = sqrtf(w*w + x*x + y*y + z*z);
    w /= len;
    x /= len;
    y /= len;
    z /= len;
}

Vector3D Quaternion::rotate(const Vector3D& vector) const {
    Vector3D rotated_vector;

    rotated_vector.x = (1 - 2*y*y - 2*z*z) * vector.x + 2 * (x*y - z*w) * vector.y + 2 * (x*z + y*w) * vector.z;
    rotated_vector.y = 2 * (x*y + z*w) * vector.x + (1 - 2*x*x - 2*z*z) * vector.y + 2 * (y*z - x*w) * vector.z;
    rotated_vector.z = 2 * (x*z - y*w) * vector.x + 2 * (y*z + x*w) * vector.y + (1 - 2*x*x - 2*y*y) * vector.z;

    return rotated_vector;
}

Quaternion Quaternion::operator*(const Quaternion &q) const {
    Quaternion result;
    result.w = w * q.w - x * q.x - y * q.y - z * q.z;
    result.x = w * q.x + x * q.w + y * q.z - z * q.y;
    result.y = w * q.y - x * q.z + y * q.w + z * q.x;
    result.z = w * q.z + x * q.y - y * q.x + z * q.w;
    return result;
}
