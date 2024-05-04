#include "Object.h"

void Object::setMaterial(IMaterial* material) {
    this->material = material;
}

IMaterial* Object::getMaterial() const {
    return material;
}

Mesh* Object::getMesh() const {
    return mesh;
}
