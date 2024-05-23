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
    std::vector<unsigned int> indexes;
    std::vector<TrianglePtr> triangles;
    std::vector<Vector3D> vertices;
    std::unique_ptr<BoundingBox> boundingBox;

public:
    Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indexes);

    static Vector3D calculateCenter(float* vertices, size_t size);

    void reset();
    void applyTransform(const Transform& transform);
    void applyMorph(const std::vector<unsigned int>& indexes, const std::vector<float>& morphVertices, float weight);
    const std::vector<TrianglePtr>& getTriangles() const;
    const std::unique_ptr<BoundingBox>& getBoundingBox() const;
};
