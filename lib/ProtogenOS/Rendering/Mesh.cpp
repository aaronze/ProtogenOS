#include "Mesh.h"

Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indexes) {
    Vector3D minCorner = Vector3D(999999, 999999, 999999);
    Vector3D maxCorner = Vector3D(-999999, -999999, -999999);

    for (size_t i = 0; i < vertices.size(); i+=3) {
        Vector3D vector = Vector3D(vertices[i], vertices[i+1], vertices[i+2]);
        this->originalVertices.push_back(vector.clone());
        this->vertices.push_back(vector.clone());

        if (vector.x < minCorner.x) minCorner.x = vector.x;
        if (vector.y < minCorner.y) minCorner.y = vector.y;
        if (vector.z < minCorner.z) minCorner.z = vector.z;
        if (vector.x > maxCorner.x) maxCorner.x = vector.x;
        if (vector.y > maxCorner.y) maxCorner.y = vector.y;
        if (vector.z > maxCorner.z) maxCorner.z = vector.z;
    }
    this->boundingBox = std::make_unique<BoundingBox>(minCorner, maxCorner);

    for (size_t i = 0; i < indexes.size(); i+=3) {
        TrianglePtr triangle = std::make_shared<Triangle>(
            &this->vertices[indexes[i]],
            &this->vertices[indexes[i+1]],
            &this->vertices[indexes[i+2]]
        );
        this->triangles.push_back(triangle);
    }

    this->indexes = std::move(indexes);
}

Vector3D Mesh::calculateCenter(float* vertices, size_t size) {
    Vector3D min;
    Vector3D max;
    for (size_t i = 0; i < size; i+=3) {
        Vector3D vertex(vertices[i], vertices[i+1], vertices[i+2]);
        if (i == 0) {
            min = vertex;
            max = vertex;
        } else {
            min.x = std::min(min.x, vertex.x);
            min.y = std::min(min.y, vertex.y);
            min.z = std::min(min.z, vertex.z);
            max.x = std::max(max.x, vertex.x);
            max.y = std::max(max.y, vertex.y);
            max.z = std::max(max.z, vertex.z);
        }
    }
    return (min + max) / 2.0f;
}

void Mesh::reset() {
    for (size_t i = 0; i < originalVertices.size(); i++) {
        vertices[i] = originalVertices[i];
    }
}

void Mesh::applyTransform(const Transform& transform) {
    boundingBox->applyTransform(transform);
    for (auto& vertex : vertices) {
        transform.apply(vertex);
    }
}

void Mesh::applyMorph(const std::vector<unsigned int>& morphIndexes, const std::vector<float>& morphVertices, float weight) {
    for (size_t i = 0; i < morphIndexes.size(); i++) {
        vertices[morphIndexes[i]].add(morphVertices[i*3] * weight, morphVertices[i*3+1] * weight, morphVertices[i*3+2] * weight);
    }
}

const std::vector<TrianglePtr>& Mesh::getTriangles() const {
    return triangles;
}

const std::unique_ptr<BoundingBox>& Mesh::getBoundingBox() const {
    return boundingBox;
}
