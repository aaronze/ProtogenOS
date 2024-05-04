#pragma once

#include "Rendering/Materials/IMaterial.h"
#include "Rendering/Mesh.h"

class Object {
private:
    Mesh* mesh;
    IMaterial* material;

public:
    explicit Object(Mesh* mesh, IMaterial* material) : mesh(mesh), material(material) {};

    void setMaterial(IMaterial* material);
    IMaterial* getMaterial() const;
    Mesh* getMesh() const;
};
