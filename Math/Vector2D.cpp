#include "Vector2D.h"

bool Vector2D::operator ==(const Vector2D& vector) const {
    return x == vector.x && y == vector.y;
}

bool Vector2D::operator !=(const Vector2D& vector) const {
    return x != vector.x || y != vector.y;
}

Vector2D Vector2D::operator +=(const Vector2D& vector) {
    x += vector.x;
    y += vector.y;
    return *this;
}

Vector2D Vector2D::operator =(const Vector2D& vector) {
    x = vector.x;
    y = vector.y;
    return *this;
}

Vector2D Vector2D::operator +(const Vector2D& vector) const {
    return {x + vector.x, y + vector.y };
}

Vector2D Vector2D::operator -(const Vector2D& vector) const {
    return {x - vector.x, y - vector.y };
}

Vector2D Vector2D::operator +(const float& value) const {
    return {x + value, y + value };
}

Vector2D Vector2D::operator -(const float& value) const {
    return {x - value, y - value };
}

Vector2D Vector2D::operator *(const float& value) const {
    return {x * value, y * value };
}

Vector2D Vector2D::operator /(const float& value) const {
    return {x / value, y / value };
}