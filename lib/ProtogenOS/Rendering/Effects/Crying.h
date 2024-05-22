#pragma once

#include <vector>
#include <random>
#include "IEffect.h"
#include "Particles/Tear.h"
#include "Rendering/Scene.h"

class Crying : public IEffect {
private:
    std::shared_ptr<Scene> scene;
    std::vector<std::shared_ptr<Object>> tears;
    Vector3D target;

public:
    explicit Crying(std::shared_ptr<Scene>& scene, Vector3D target, unsigned int numberOfTears = 5, unsigned long duration = 1000000) : IEffect(duration) {
        this->scene = scene;
        this->target = target;

        for (unsigned int i = 0; i < numberOfTears; i++) {
            auto tear = std::make_shared<Tear>();
            tear->getTransform().setPosition(Vector3D(target.x + (std::rand() % 10 - 5) / 32.0f, target.y + (std::rand() % 10 - 5) / 16.0f, 0));
            tears.push_back(tear);
        }

        for (auto& tear : tears) {
            scene->addObject(tear);
        }
    }

    ~Crying() override {
        for (auto& tear : tears) {
            scene->removeObject(tear);
        }
        tears.clear();
    }

    void update(unsigned long delta) override {
        for (auto& tear : tears) {
            auto position = tear->getTransform().getPosition();
            if (position.y > target.y) position.y -= 5.0f / 16.0f;
            tear->getTransform().setPosition(Vector3D(position.x, position.y + float(delta) / 1400.0f, 0));
        }
    }
};
