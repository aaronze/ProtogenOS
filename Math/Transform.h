#pragma once

#include "Vector3D.h"

class Transform {
private:
    Vector3D position;

public:
    void translate(const Vector3D translation);

    void apply(Vector3D& vector) const;
};
