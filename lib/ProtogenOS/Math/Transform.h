#pragma once

#include "Quaternion.h"
#include "Vector3D.h"

class Transform {
private:
    Vector3D origin;
    Vector3D position;
    Vector3D scale = {1.0f, 1.0f, 1.0f};
    Quaternion rotation = {1.0f, 0.0f, 0.0f, 0.0f};

public:
    void setOrigin(Vector3D origin) {
        this->origin = origin;
    }

    Vector3D getOrigin() {
        return origin;
    }

    void setPosition(const Vector3D position) {
        this->position = position;
    }

    Vector3D getPosition() {
        return position;
    }

    void setScale(const Vector3D scale) {
        this->scale = scale;
    }

    Vector3D getScale() {
        return scale;
    }

    void setRotation(const float& angleInDegrees, const Vector3D& axis) {
        this->rotation = Quaternion::createRotationQuaternion(angleInDegrees, axis);
    }

    void addRotation(const float& angleInDegrees, const Vector3D& axis) {
        this->rotation = this->rotation * Quaternion::createRotationQuaternion(angleInDegrees, axis);
    }

    Quaternion getRotation() {
        return rotation;
    }

    void apply(Vector3D& vector) const {
        vector -= origin;
        vector *= scale;
        vector = rotation.rotate(vector);
        vector += position;
    }

    Vector3D transform(Vector3D vector) const {
        auto vec = vector.clone();
        apply(vec);
        return vec;
    }
};
