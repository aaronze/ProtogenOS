#pragma once

#include <Arduino.h>
#include "Rendering/Object.h"

enum Morph {
    Blink,
    Love,
    Surprised,
    Anger,
    Frown,
    HideBlush,
};

class IFace : public Object {
private:
    std::unordered_map<Morph, std::vector<unsigned int>> morphIndexes;
    std::unordered_map<Morph, std::vector<float>> morphVertices;
    std::unordered_map<Morph, float> morphWeights;

    Vector2D getWiggle(float amplitude = 5.0f) {
        auto xPeriod = 5.3f / amplitude;
        auto yPeriod = 6.7f / amplitude;

        auto time = micros() / 1000000.0f;
        auto xTime = fmod(time, xPeriod);
        auto yTime = fmod(time, yPeriod);

        auto xWave = sinf(xTime / xPeriod * 2.0f * 3.14159f);
        auto yWave = sinf(yTime / yPeriod * 2.0f * 3.14159f);

        xWave = min(max(xWave, -2.0f), 2.0f);
        yWave = min(max(yWave, -2.0f), 2.0f);

        return {xWave, yWave};
    }

protected:
    void addMorph(Morph morph, unsigned int count, unsigned int indexes[], float vertices[]) {
        std::vector<unsigned int> indexList (indexes, indexes + count);
        std::vector<float> vertexList (vertices, vertices + count * 3);

        morphIndexes[morph] = indexList;
        morphVertices[morph] = vertexList;
    }

public:
    virtual ~IFace() = default;

    void update() override {
        getMesh()->reset();

        for (const auto& morphWeight : morphWeights) {
            Morph morph = morphWeight.first;
            float weight = morphWeight.second;

            const auto& indexes = morphIndexes[morph];
            const auto& vertices = morphVertices[morph];

            getMesh()->applyMorph(indexes, vertices, weight);
        }

        auto wiggle = getWiggle(2.5f);
        getTransform().translate({wiggle.x, wiggle.y, 0});
        getMesh()->applyTransform(getTransform());
    }

    void reset() {
        morphWeights.clear();
    }

    void morph(Morph morph, float weight = 1.0f) {
        morphWeights[morph] = weight;
    }
};