#pragma once

#include "Vector3D.h"

class Transform {
private:
    Vector3D position;

public:
    Vector3D getPosition() {
        return position;
    }

    void translate(const Vector3D translation) {
        position = translation;
    }

    void apply(Vector3D& vector) const {
        vector += position;
    }

    Vector3D transform(Vector3D vector) const {
        auto vec = vector.clone();
        apply(vec);
        return vec;
    }
};
