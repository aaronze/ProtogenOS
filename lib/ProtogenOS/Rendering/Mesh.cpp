#include "Mesh.h"

Mesh::Mesh(std::vector<Vector3D> vertices, std::vector<uint32_t> indexes) {
    Vector3D minCorner;
    Vector3D maxCorner;
    for (const auto& vector : vertices) {
        this->vertices.push_back(vector.clone());

        if (vector.x < minCorner.x) minCorner.x = vector.x;
        if (vector.y < minCorner.y) minCorner.y = vector.y;
        if (vector.z < minCorner.z) minCorner.z = vector.z;
        if (vector.x > maxCorner.x) maxCorner.x = vector.x;
        if (vector.y > maxCorner.y) maxCorner.y = vector.y;
        if (vector.z > maxCorner.z) maxCorner.z = vector.z;
    }
    this->boundingBox = new BoundingBox(minCorner, maxCorner);

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

Mesh::~Mesh() {
    delete boundingBox;
}

void Mesh::restore() {
    for (size_t i = 0; i < originalVertices.size(); i++) {
        vertices[i] = originalVertices[i];
    }
}

void Mesh::applyTransform(Transform& transform) {
    boundingBox->applyTransform(&transform);
    for (size_t i = 0; i < originalVertices.size(); i++) {
        transform.apply(vertices[i]);
    }
}

std::vector<TrianglePtr> Mesh::getTriangles() {
    return triangles;
}

BoundingBox* Mesh::getBoundingBox() {
    return boundingBox;
}
