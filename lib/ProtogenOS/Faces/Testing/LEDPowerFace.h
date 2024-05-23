#pragma once

#include "Faces/IFace.h"
#include "Rendering/UI/Text2D.h"

/**
 * 0 ---------- 1
 * |------------|
 * |------------|
 * 2 ---------- 3
 * 4 -- 5
 * 6 -- 7
 */
class LEDPowerFace : public IFace {
private:
    size_t width;
    size_t height;
    unsigned long activeLEDs = 0;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<IMaterial> white = std::make_shared<SolidMaterial>(0xFFFFFF);

    std::vector<float> morphVertexList;
    std::vector<unsigned int> morphIndexList;

public:
    LEDPowerFace(size_t width, size_t height) : width(width), height(height) {
        float vertices[27] = {
                -1, -1, 0,
                1, -1, 0,
                -1, -1, 0,
                1, -1, 0,
                -1, -1, 0,
                -1, -1, 0,
                -1, -1, 0,
                -1, -1, 0,
                1, 1, 0,
        };
        unsigned int indexes[12] = {0, 1, 2, 1, 3, 2, 4, 5, 6, 5, 7, 6};

        auto indexList = std::vector<unsigned int>(indexes, indexes + 12);
        auto vertexList = std::vector<float>(vertices, vertices + 27);

        mesh = std::make_shared<Mesh>(vertexList, indexList);
        setMesh(mesh);

        float morphVertices[24] = {
                0, -2, 0,
                0, 0, 0,
                0, 0, 0,
                0, 0, 0,
                0, 0, 0,
                0, 0, 0,
                0, 0, 0,
                0, 0, 0,
        };
        unsigned int morphIndexes[8] = {0, 1, 2, 3, 4, 5, 6, 7};

        morphIndexList = std::vector<unsigned int>(morphIndexes, morphIndexes + 8);
        morphVertexList = std::vector<float>(morphVertices, morphVertices + 24);
    }

    void update(unsigned long delta) override {
        activeLEDs = (activeLEDs + 1) % (width * height);

        auto w = activeLEDs % width;
        auto h = activeLEDs / width;

        if (h > 0) {
            morphVertexList[7] = (h - 1) * (2.0f / height);
            morphVertexList[10] = (h - 1) * (2.0f / height);
            morphVertexList[13] = (h - 1) * (2.0f / height);
            morphVertexList[16] = (h - 1) * (2.0f / height);

            morphVertexList[19] = h * (2.0f / height);
            morphVertexList[22] = h * (2.0f / height);
        }
        morphVertexList[15] = w * (2.0f / width);
        morphVertexList[21] = w * (2.0f / width);

        getMesh()->reset();
        getMesh()->applyMorph(morphIndexList, morphVertexList, 1.0f);
        getMesh()->applyTransform(getTransform());

        setMaterial(white);
    }
};
