#pragma once

#include "Rendering/Object.h"
#include "Rendering/Materials/SolidMaterial.h"

class Heart : public Object {
public:
    Heart() {
        Vector3D vertices[13] = {Vector3D(-4.5809f,-4.3435f,0.451f),Vector3D(-0.0622f,-0.0715f,0.451f),Vector3D(2.6902f,2.0993f,0.451f),Vector3D(2.0204f,-4.5105f,0.451f),Vector3D(-5.2689f,-0.1445f,0.451f),Vector3D(-5.5342f,-2.4037f,0.451f),Vector3D(5.5477f,-2.2884f,0.451f),Vector3D(-0.0399f,3.8837f,0.451f),Vector3D(-0.0386f,-2.6716f,0.451f),Vector3D(-3.5036f,1.9333f,0.451f),Vector3D(-1.8956f,-4.5798f,0.451f),Vector3D(4.8865f,-0.0505f,0.451f),Vector3D(4.4649f,-4.3791f,0.451f)};
        uint32_t indexes[36] = {1,2,11,1,5,4,10,0,5,12,3,1,1,7,2,1,9,7,8,10,1,6,1,11,9,1,4,1,10,5,3,8,1,6,12,1};

        std::vector<Vector3D> vertexList (std::begin(vertices), std::end(vertices));
        std::vector<uint32_t> indexList (std::begin(indexes), std::end(indexes));

        setMaterial(new SolidMaterial(0xFF0000));
        setMesh(new Mesh(vertexList, indexList));
    }
};
