#include "Object.h"

void Object::setMaterial(std::shared_ptr<IMaterial> material) {
    this->material = std::move(material);
}

const std::shared_ptr<IMaterial>& Object::getMaterial() const {
    return material;
}

void Object::setMesh(std::shared_ptr<Mesh> mesh) {
    this->mesh = std::move(mesh);
}

const std::shared_ptr<Mesh>& Object::getMesh() const {
    return mesh;
}

void Object::setTransform(Transform& transform) {
    this->transform = transform;
}

Transform& Object::getTransform() {
    return transform;
}
