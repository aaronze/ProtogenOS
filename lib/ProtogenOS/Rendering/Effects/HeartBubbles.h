#pragma once

#include <random>
#include <vector>
#include "Animation/Tween.h"
#include "IEffect.h"
#include "Math/Generators/SineGenerator.h"
#include "Particles/Heart.h"
#include "Rendering/Scene.h"

class HeartBubbles : public IEffect {
private:
    std::shared_ptr<Scene> scene;
    std::vector<std::shared_ptr<Object>> hearts;
    std::vector<std::shared_ptr<Tween>> tweens;

public:
    explicit HeartBubbles(std::shared_ptr<Scene>& scene, unsigned int numberOfHearts = 5, unsigned long duration = 3000) : IEffect(duration) {
        this->scene = scene;

        for (unsigned int i = 0; i < numberOfHearts; i++) {
            float duration = 4.0f;
            float x = -1.0f + (2.0f / numberOfHearts) * i;
            float startX = x + (std::rand() % 4) / 32.0f;
            float startY = 4.0f - (std::rand() % 40) / 16.0f;
            float startZ = -10.0f;

            auto heart = std::make_shared<Heart>();
            hearts.push_back(heart);

            auto tween = std::make_shared<Tween>(heart->getTransform());
            tween->addKeyFrame(KeyFrame::fromMove(startX, startY, startZ), 0.0f, 0.0f);
            tween->addKeyFrame(KeyFrame::fromScale(0.16f, 0.16f, 1.0f), 0.0f, 0.0f);
            tween->addKeyFrame(KeyFrame::fromMove(0.0f, -(float(std::rand() % 7) + 7.0f)), 0.0f, duration);

            std::unique_ptr<IGenerator> wobbleGen = std::make_unique<SineGenerator>((std::rand() % 360) / M_PI, 1.0f, (std::rand() % 4 + 4) / 8.0f);
            auto wobble = std::make_unique<KeyFrame>(KeyFrame::fromScale(0.15f, 0.15f, 0.2f), 0.0f, duration, wobbleGen);
            tween->addKeyFrame(wobble);

            tweens.push_back(tween);
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
        tweens.clear();
    }

    void update(unsigned long delta) override {
        for (auto& tween : tweens) {
            tween->update(delta);
        }
    }
};
