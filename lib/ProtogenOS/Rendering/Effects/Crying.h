#pragma once

#include <vector>
#include <random>
#include "IEffect.h"
#include "Particles/Tear.h"
#include "Rendering/Scene.h"

class Crying : public IEffect {
private:
    Scene* scene;
    std::vector<Tear*> tears;

public:
    explicit Crying(Scene* scene, unsigned int numberOfTears = 5, unsigned long duration = 10000);
    ~Crying() override;

    void update(unsigned long delta) override;
};
