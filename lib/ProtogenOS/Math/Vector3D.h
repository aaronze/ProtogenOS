#pragma once

class Vector3D {
public:
    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

    float x, y, z;

    float length() const;
    Vector3D normalize();
    Vector3D cross(const Vector3D& vector) const;
    float dot(const Vector3D& vector) const;
    Vector3D clone() const;
    void add(float x, float y, float z);
    void set(float x, float y, float z);

    bool operator ==(const Vector3D& vector) const;
    bool operator !=(const Vector3D& vector) const;
    Vector3D& operator +=(const Vector3D& vector);
    Vector3D& operator -=(const Vector3D& vector);
    Vector3D& operator *=(const Vector3D& vector);
    Vector3D& operator =(const Vector3D& vector) = default;
    Vector3D operator +(const Vector3D& vector) const;
    Vector3D operator -(const Vector3D& vector) const;
    Vector3D operator *(const Vector3D& vector) const;
    Vector3D operator +(const float& value) const;
    Vector3D operator -(const float& value) const;
    Vector3D operator *(const float& value) const;
    Vector3D operator /(const float& value) const;
};
