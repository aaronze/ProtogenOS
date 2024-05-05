#include "Vector3D.h"
#include <math.h>

float Vector3D::length() const {
    return sqrtf(x * x + y * y + z * z);
}

Vector3D Vector3D::normalize() {
    float length = this->length();
    x /= length;
    y /= length;
    z /= length;
    return *this;
}

Vector3D Vector3D::cross(const Vector3D &vector) const {
    return {
        y * vector.z - z * vector.y,
        z * vector.x - x * vector.z,
        x * vector.y - y * vector.x
    };
}

float Vector3D::dot(const Vector3D &vector) const {
    return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

Vector3D Vector3D::clone() const {
    return Vector3D({x, y, z});
}

bool Vector3D::operator ==(const Vector3D& vector) const {
    return x == vector.x && y == vector.y && z == vector.z;
}

bool Vector3D::operator !=(const Vector3D& vector) const {
    return x != vector.x || y != vector.y || z != vector.z;
}

Vector3D Vector3D::operator +=(const Vector3D& vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Vector3D Vector3D::operator =(const Vector3D& vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
}

Vector3D Vector3D::operator +(const Vector3D& vector) const {
    return {x + vector.x, y + vector.y, z + vector.z };
}

Vector3D Vector3D::operator -(const Vector3D& vector) const {
    return {x - vector.x, y - vector.y, z - vector.z };
}

float Vector3D::operator *(const Vector3D& vector) const {
    return (x * vector.x) + (y * vector.y) + (z * vector.z);
}

Vector3D Vector3D::operator +(const float& value) const {
    return {x + value, y + value, z + value };
}

Vector3D Vector3D::operator -(const float& value) const {
    return {x - value, y - value, z - value };
}

Vector3D Vector3D::operator *(const float& value) const {
    return {x * value, y * value, z * value };
}

Vector3D Vector3D::operator /(const float& value) const {
    return {x / value, y / value, z / value };
}
