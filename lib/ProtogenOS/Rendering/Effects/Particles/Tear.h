#pragma once

#include "Rendering/Object.h"
#include "Rendering/Materials/SolidMaterial.h"

class Tear : public Object {
public:
    Tear() {
        float vertices[12] = {-0.6237f,4.9957f,0.451f,-0.5351f,-5.5195f,0.451f,0.8966f,-5.5165f,0.451f,0.7885f,5.0347f,0.451f};
        unsigned int indexes[6] = {3,0,2,2,0,1};

        std::vector<float> vertexList (std::begin(vertices), std::end(vertices));
        std::vector<unsigned int> indexList (std::begin(indexes), std::end(indexes));

        setMaterial(new SolidMaterial(0x0000FF));
        setMesh(new Mesh(vertexList, indexList));
    }
};

