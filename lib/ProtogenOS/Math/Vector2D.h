#pragma once

class Vector2D {
public:
    Vector2D() : x(0), y(0) {}
    Vector2D(float x, float y) : x(x), y(y) {}

    float x, y;

    bool operator ==(const Vector2D& vector) const;
    bool operator !=(const Vector2D& vector) const;
    Vector2D operator +=(const Vector2D& vector);
    Vector2D operator =(const Vector2D& vector);
    Vector2D operator +(const Vector2D& vector) const;
    Vector2D operator -(const Vector2D& vector) const;
    Vector2D operator +(const float& value) const;
    Vector2D operator -(const float& value) const;
    Vector2D operator *(const float& value) const;
    Vector2D operator /(const float& value) const;
};
