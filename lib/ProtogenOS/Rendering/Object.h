#pragma once

#include "Math/Transform.h"
#include "Rendering/Materials/IMaterial.h"
#include "Rendering/Mesh.h"

class Object {
protected:
    Transform transform;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<IMaterial> material;

public:
    Object() = default;
    Object(Mesh* mesh, IMaterial* material) : mesh(mesh), material(material) {}
    virtual ~Object() = default;

    virtual void update(unsigned long delta) {
        material->update(delta);

        mesh->reset();
        mesh->applyTransform(transform);
    }

    virtual void setMaterial(std::shared_ptr<IMaterial> material);
    const std::shared_ptr<IMaterial>& getMaterial() const;

    void setMesh(std::shared_ptr<Mesh> mesh);
    const std::shared_ptr<Mesh>& getMesh() const;

    void setTransform(Transform& transform);
    Transform& getTransform();
};
