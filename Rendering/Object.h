#pragma once

#include <vector>
#include <memory>
#include "Math/Triangle.h"
#include "Rendering/Materials/Material.h"

using TrianglePtr = std::shared_ptr<Triangle>;

class Object {
private:
    std::vector<TrianglePtr> triangles;
    Material* material;

public:
    explicit Object(Material* material) : material(material) {};

    void addTriangle(const TrianglePtr& triangle);
    const std::vector<TrianglePtr>& getTriangles() const;
    Material *const getMaterial() const;
};
