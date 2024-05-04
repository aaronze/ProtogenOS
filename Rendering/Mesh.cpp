#include "Mesh.h"

Mesh::Mesh(std::vector<Vector3D> vertices, std::vector<uint32_t> indexes) {
    for (size_t i = 0; i < indexes.size(); i += 3) {
        TrianglePtr triangle = std::make_shared<Triangle>(vertices[indexes[i]], vertices[indexes[i + 1]],vertices[indexes[i + 2]]);
        this->triangles.push_back(triangle);
    }

    for (const auto& vector : vertices) {
        this->vertices.push_back(vector.clone());
    }

    this->originalVertices = std::move(vertices);
    this->indexes = std::move(indexes);
}

void Mesh::restore() {
    for (size_t i = 0; i < originalVertices.size(); i++) {
        vertices[i] = originalVertices[i];
    }
}

std::vector<TrianglePtr> Mesh::getTriangles() {
    return triangles;
}
