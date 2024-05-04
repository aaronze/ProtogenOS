#pragma once

#include <memory>
#include <vector>
#include "Math/Triangle.h"
#include "Math/Vector3D.h"

using TrianglePtr = std::shared_ptr<Triangle>;

class Mesh {
private:
    std::vector<Vector3D> originalVertices;
    std::vector<uint32_t> indexes;
    std::vector<TrianglePtr> triangles;
    std::vector<Vector3D> vertices;

public:
    Mesh() {};
    Mesh(std::vector<Vector3D> vertices, std::vector<uint32_t> indexes);

    void restore();
    std::vector<TrianglePtr> getTriangles();
};
