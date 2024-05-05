#pragma once

#include <vector>
#include <random>
#include "IEffect.h"
#include "Particles/Heart.h"
#include "Rendering/Scene.h"

class HeartBubbles : public IEffect {
private:
    Scene* scene;
    std::vector<Heart*> hearts;

public:
    explicit HeartBubbles(Scene* scene, unsigned int numberOfHearts = 5, unsigned long duration = 10000);
    ~HeartBubbles() override;

    void update(unsigned long delta) override;
};
