#include "Mesh.h"

Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indexes) {
    Vector3D minCorner;
    Vector3D maxCorner;

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
    this->boundingBox = new BoundingBox(minCorner, maxCorner);

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

Mesh::~Mesh() {
    delete boundingBox;
}

void Mesh::reset() {
    for (size_t i = 0; i < originalVertices.size(); i++) {
        vertices[i] = originalVertices[i];
    }
}

void Mesh::applyTransform(Transform& transform) {
    boundingBox->applyTransform(&transform);
    for (auto& vertex : vertices) {
        transform.apply(vertex);
    }
}

std::vector<TrianglePtr> Mesh::getTriangles() {
    return triangles;
}

BoundingBox* Mesh::getBoundingBox() {
    return boundingBox;
}

void Mesh::applyMorph(std::vector<unsigned int> morphIndexes, std::vector<float> morphVertices, float weight) {
    for (size_t i = 0; i < morphIndexes.size(); i++) {
        vertices[morphIndexes[i]].add(morphVertices[i*3] * weight, morphVertices[i*3+1] * weight, morphVertices[i*3+2] * weight);
    }
}
