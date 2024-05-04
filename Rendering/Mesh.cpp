#include "Mesh.h"

Mesh::Mesh(std::vector<Vector3D> vertices, std::vector<uint32_t> indexes) {
    for (const auto& vector : vertices) {
        this->vertices.push_back(vector.clone());
    }

    for (size_t i = 0; i < indexes.size(); i += 3) {
        TrianglePtr triangle = std::make_shared<Triangle>(
            &this->vertices[indexes[i]],
            &this->vertices[indexes[i+1]],
            &this->vertices[indexes[i+2]]
        );
        this->triangles.push_back(triangle);
    }

    this->originalVertices = std::move(vertices);
    this->indexes = std::move(indexes);
}

void Mesh::restore() {
    for (size_t i = 0; i < originalVertices.size(); i++) {
        vertices[i] = originalVertices[i];
    }
}

void Mesh::applyTransform(Transform& transform) {
    for (size_t i = 0; i < originalVertices.size(); i++) {
        transform.apply(vertices[i]);
    }
}

std::vector<TrianglePtr> Mesh::getTriangles() {
    return triangles;
}
