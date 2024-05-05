#include "Object.h"

Object::~Object() {
    delete material;
    delete mesh;
}

void Object::setMaterial(IMaterial* material) {
    this->material = material;
}

IMaterial* Object::getMaterial() const {
    return material;
}

void Object::setMesh(Mesh* mesh) {
    this->mesh = mesh;
}

Mesh* Object::getMesh() const {
    return mesh;
}

void Object::setTransform(Transform transform) {
    this->transform = transform;
}

Transform& Object::getTransform() {
    return transform;
}
