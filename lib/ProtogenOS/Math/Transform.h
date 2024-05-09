#pragma once

#include "Quaternion.h"
#include "Vector3D.h"

class Transform {
private:
    Vector3D position;
    Vector3D scale = {1.0f, 1.0f, 1.0f};
    Quaternion rotation = {1.0f, 0.0f, 0.0f, 0.0f};

public:
    Vector3D getPosition() {
        return position;
    }

    Vector3D getScale() {
        return scale;
    }

    void setPosition(const Vector3D position) {
        this->position = position;
    }

    void setScale(const Vector3D scale) {
        this->scale = scale;
    }

    void setRotation(const float& angleInDegrees, const Vector3D& axis) {
        rotation = Quaternion::createRotationQuaternion(angleInDegrees, axis);
    }

    void apply(Vector3D& vector) const {
        vector.x = vector.x * scale.x;
        vector.y = vector.y * scale.y;
        vector.z = vector.z * scale.z;

        vector = rotation.rotate(vector);

        vector += position;
    }

    Vector3D transform(Vector3D vector) const {
        auto vec = vector.clone();
        apply(vec);
        return vec;
    }
};
