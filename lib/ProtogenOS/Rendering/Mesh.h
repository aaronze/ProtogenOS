#pragma once

#include <memory>
#include <vector>
#include "Math/BoundingBox.h"
#include "Math/Transform.h"
#include "Math/Triangle.h"
#include "Math/Vector3D.h"

using TrianglePtr = std::shared_ptr<Triangle>;

class Mesh {
private:
    std::vector<Vector3D> originalVertices;
    std::vector<uint32_t> indexes;
    std::vector<TrianglePtr> triangles;
    std::vector<Vector3D> vertices;
    BoundingBox* boundingBox;

public:
    Mesh() = default;
    Mesh(std::vector<Vector3D> vertices, std::vector<uint32_t> indexes);
    ~Mesh();

    void reset();
    void applyTransform(Transform& transform);
    void applyMorph(std::vector<unsigned int> indexes, std::vector<float> morphVertices, float weight);
    std::vector<TrianglePtr> getTriangles();
    BoundingBox* getBoundingBox();
};
