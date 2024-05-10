#pragma once

#include "Math/Transform.h"
#include "Rendering/Materials/IMaterial.h"
#include "Rendering/Mesh.h"

class Object {
private:
    Transform transform;
    Mesh* mesh;
    IMaterial* material;

public:
    Object() = default;
    Object(Mesh* mesh, IMaterial* material) : mesh(mesh), material(material) {}
    virtual ~Object();

    virtual void update(unsigned long delta) {
        material->update(delta);

        mesh->reset();
        mesh->applyTransform(transform);
    }

    void setMaterial(IMaterial* material);
    IMaterial* getMaterial() const;

    void setMesh(Mesh* mesh);
    Mesh* getMesh() const;

    void setTransform(Transform transform);
    Transform& getTransform();
};
