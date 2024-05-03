#include "Object.h"

void Object::addTriangle(const TrianglePtr &triangle) {
    triangles.push_back(triangle);
}

const std::vector<TrianglePtr>& Object::getTriangles() const {
    return triangles;
}

Material *const Object::getMaterial() const {
    return material;
}
