#include "Quaternion.h"

#include <math.h>

Quaternion Quaternion::createRotationQuaternion(const float angleInDegrees, const Vector3D axis) {
    float angleInRadians = (angleInDegrees / 180.0f) * 3.14159f;
    float s = sinf(angleInRadians / 2.0f);
    return Quaternion(cosf(angleInRadians / 2.0f), axis.x * s, axis.y * s, axis.z * s);
}

Vector3D Quaternion::rotate(const Vector3D& vector) const {
    Vector3D rotated_vector;

    rotated_vector.x = (1 - 2*y*y - 2*z*z) * vector.x + 2 * (x*y - z*w) * vector.y + 2 * (x*z + y*w) * vector.z;
    rotated_vector.y = 2 * (x*y + z*w) * vector.x + (1 - 2*x*x - 2*z*z) * vector.y + 2 * (y*z - x*w) * vector.z;
    rotated_vector.z = 2 * (x*z - y*w) * vector.x + 2 * (y*z + x*w) * vector.y + (1 - 2*x*x - 2*y*y) * vector.z;

    return rotated_vector;
}
