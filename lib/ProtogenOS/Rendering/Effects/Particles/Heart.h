#pragma once

#include "Rendering/Object.h"
#include "Rendering/Materials/SolidMaterial.h"

class Heart : public Object {
public:
    Heart() {
        float vertices[39] = {-4.58f,-4.34f,0.45f,-0.06f,-0.07f,0.45f,2.69f,2.1f,0.45f,2.02f,-4.51f,0.45f,-5.27f,-0.14f,0.45f,-5.53f,-2.4f,0.45f,5.55f,-2.29f,0.45f,-0.04f,3.88f,0.45f,-0.04f,-2.67f,0.45f,-3.5f,1.93f,0.45f,-1.9f,-4.58f,0.45f,4.89f,-0.05f,0.45f,4.46f,-4.38f,0.45f};
        unsigned int indexes[36] = {1,2,11,1,5,4,10,0,5,12,3,1,1,7,2,1,9,7,8,10,1,6,1,11,9,1,4,1,10,5,3,8,1,6,12,1};

        std::vector<float> vertexList (std::begin(vertices), std::end(vertices));
        std::vector<unsigned int> indexList (std::begin(indexes), std::end(indexes));

        Transform importTransform;
        importTransform.setScale(Vector3D(1.0f / 32, 1.0f / 16, 1.0f / 16));
        importTransform.apply(vertexList);

        auto material = std::make_shared<SolidMaterial>(0xFF0000);
        setMaterial(std::move(material));

        auto mesh = std::make_shared<Mesh>(vertexList, indexList);
        setMesh(std::move(mesh));
    }
};
