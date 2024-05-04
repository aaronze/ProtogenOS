#include "Transform.h"

void Transform::translate(const Vector3D translation) {
    position = translation;
}

void Transform::apply(Vector3D& vector) const {
    vector += position;
}
