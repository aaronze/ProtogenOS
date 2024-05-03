#pragma once

#include <vector>
#include <memory>
#include "../Math/Triangle.h"

using TrianglePtr = std::shared_ptr<Triangle>;

class Object {
private:
    std::vector<TrianglePtr> triangles;

public:
    void addTriangle(const TrianglePtr& triangle);
    const std::vector<TrianglePtr>& getTriangles() const;
};
