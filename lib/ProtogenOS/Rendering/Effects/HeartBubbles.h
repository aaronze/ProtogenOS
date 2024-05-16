#pragma once

#include <vector>
#include <random>
#include "IEffect.h"
#include "Particles/Heart.h"
#include "Rendering/Scene.h"

class HeartBubbles : public IEffect {
private:
    std::shared_ptr<Scene> scene;
    std::vector<std::shared_ptr<Object>> hearts;

public:
    explicit HeartBubbles(std::shared_ptr<Scene>& scene, unsigned int numberOfHearts = 5, unsigned long duration = 3000) : IEffect(duration) {
        this->scene = scene;

        for (unsigned int i = 0; i < numberOfHearts; i++) {
            float x = -1.0f + (2.0f / numberOfHearts) * i;

            auto heart = std::make_shared<Heart>();
            heart->getTransform().setPosition(Vector3D(x + (std::rand() % 4) / 32.0f, 4.0f - (std::rand() % 40) / 16.0f, 0));
            hearts.push_back(heart);
        }

        for (auto& heart : hearts) {
            scene->addObject(heart);
        }
    }

    ~HeartBubbles() override {
        for (auto& heart : hearts) {
            scene->removeObject(heart);
        }
        hearts.clear();
    }

    void update(unsigned long delta) override {
        for (auto& heart : hearts) {
            auto position = heart->getTransform().getPosition();
            heart->getTransform().setPosition(Vector3D(position.x, position.y - float(delta) / 600.0f, 0));
        }
    }
};
