#include <cmath>
#include "Vector3D.h"

float Vector3D::length() const {
    return sqrtf(x * x + y * y + z * z);
}

float Vector3D::lengthSquared() const {
    return x * x + y * y + z * z;
}

Vector2D Vector3D::xy() const {
    return {x, y};
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

void Vector3D::add(float x, float y, float z) {
    this->x += x;
    this->y += y;
    this->z += z;
}

void Vector3D::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

bool Vector3D::operator ==(const Vector3D& vector) const {
    return x == vector.x && y == vector.y && z == vector.z;
}

bool Vector3D::operator !=(const Vector3D& vector) const {
    return x != vector.x || y != vector.y || z != vector.z;
}

Vector3D& Vector3D::operator +=(const Vector3D& vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Vector3D &Vector3D::operator-=(const Vector3D &vector) {
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

Vector3D& Vector3D::operator *=(const Vector3D& vector) {
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
    return *this;
}

Vector3D Vector3D::operator +(const Vector3D& vector) const {
    return {x + vector.x, y + vector.y, z + vector.z };
}

Vector3D Vector3D::operator -(const Vector3D& vector) const {
    return {x - vector.x, y - vector.y, z - vector.z };
}

Vector3D Vector3D::operator *(const Vector3D& vector) const {
    return { x * vector.x, y * vector.y, z * vector.z };
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
