#pragma once

#include <Arduino.h>
#include "Math/Transform.h"
#include "Rendering/Object.h"
#include "Rendering/Materials/BlendMaterial.h"

enum Morph {
    Blink,
    Love,
    Surprised,
    Anger,
    Frown,
    HideBlush,
    Sad,
    Happy,
};

class IFace : public Object {
private:
    std::unordered_map<Morph, std::vector<unsigned int>> morphIndexes;
    std::unordered_map<Morph, std::vector<float>> morphVertices;
    std::unordered_map<Morph, float> morphWeights;
    std::unordered_map<Morph, float> morphTargets;
    std::unordered_map<Morph, float> morphSpeeds;

    std::shared_ptr<BlendMaterial> currentBlend;
    float blinkRate = 0.0;
    unsigned int blinkCooldown = 0;

    Vector2D getWiggle(float amplitude = 2.0f) {
        auto xPeriod = 5.3f / amplitude;
        auto yPeriod = 6.7f / amplitude;

        auto time = micros() / 1000000.0f;
        auto xTime = fmod(time, xPeriod);
        auto yTime = fmod(time, yPeriod);

        auto xWave = sinf(xTime / xPeriod * 2.0f * 3.14159f);
        auto yWave = sinf(yTime / yPeriod * 2.0f * 3.14159f);

        xWave = min(max(xWave, -2.0f), 2.0f);
        yWave = min(max(yWave, -2.0f), 2.0f);

        return {xWave / 16.0f, yWave / 16.0f};
    }

protected:
    Transform importTransform;

    template<size_t triangleCount, size_t vertexCount>
    void setFace(unsigned int indexes[], float vertices[]) {
        std::vector<unsigned int> indexList (indexes, indexes + triangleCount*3);
        std::vector<float> vertexList (vertices, vertices + vertexCount*3);

        importTransform.apply(vertexList);

        auto mesh = std::make_shared<Mesh>(vertexList, indexList);
        setMesh(std::move(mesh));
    }

    void addMorph(Morph morph, unsigned int count, unsigned int indexes[], float vertices[], float morphSpeed = 0.1f) {
        std::vector<unsigned int> indexList (indexes, indexes + count);
        std::vector<float> vertexList (vertices, vertices + count * 3);

        Vector3D vec;
        for (size_t i = 0; i < count * 3; i+=3) {
            vec.set(vertexList[i], vertexList[i+1], vertexList[i+2]);
            importTransform.apply(vec);
            vertexList[i] = vec.x;
            vertexList[i+1] = vec.y;
            vertexList[i+2] = vec.z;
        }

        morphIndexes[morph] = indexList;
        morphVertices[morph] = vertexList;
        morphSpeeds[morph] = morphSpeed;
    }

public:
    virtual ~IFace() = default;

    void setBlinkRate(float blinkRate = 0.005f) {
        this->blinkRate = blinkRate;
    }

    void update(unsigned long delta) override {
        getMaterial()->update(delta);
        getMesh()->reset();

        auto willBlink = blinkRate > 0.0f && float(rand()) / float(RAND_MAX) <= blinkRate;
        if (blinkCooldown == 0 && willBlink) {
            morph(Morph::Blink, 1.0f);
            blinkCooldown = 30;
        } else if (blinkCooldown > 0) {
            if (blinkCooldown < 25) morph(Morph::Blink, 0.0f);
            blinkCooldown--;
        }

        for (const auto& morphTarget : morphTargets) {
            Morph morph = morphTarget.first;
            float target = morphTarget.second;

            if (morphWeights[morph] < target) {
                morphWeights[morph] += morphSpeeds[morph];
            }
            if (morphWeights[morph] > target) {
                morphWeights[morph] -= morphSpeeds[morph];
            }
        }

        for (const auto& morphWeight : morphWeights) {
            Morph morph = morphWeight.first;
            float weight = morphWeight.second;

            const auto& indexes = morphIndexes[morph];
            const auto& vertices = morphVertices[morph];

            getMesh()->applyMorph(indexes, vertices, weight);
        }

        auto wiggle = getWiggle();
        getTransform().setPosition({wiggle.x, wiggle.y, 0});
        getMesh()->applyTransform(getTransform());
    }

    void reset() {
        for (const auto& morphTarget : morphTargets) {
            Morph morph = morphTarget.first;
            morphTargets[morph] = 0;
        }
    }

    void morph(Morph morph, float weight = 1.0f, bool instant = false) {
        if (instant) {
            morphWeights[morph] = weight;
        }
        morphTargets[morph] = weight;
    }

    void blendMaterial(std::shared_ptr<IMaterial> to, float blendSpeed = 0.05f) {
        if (currentBlend.use_count() > 0 && currentBlend->getProgress() > 0.99f) {
            material = currentBlend->getMaterial();
            currentBlend.reset();
        }

        currentBlend = std::make_shared<BlendMaterial>(material, to, blendSpeed);
        this->material = currentBlend;
    }
};