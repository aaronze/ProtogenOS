#pragma once

#include <vector>
#include <random>
#include "Particles/Heart.h"
#include "Rendering/Scene.h"

class HeartBubbles {
private:
    Scene* scene;
    std::vector<Heart*> hearts;

public:
    HeartBubbles(Scene* scene, int numberOfHearts = 5);
    ~HeartBubbles();

    void update();
};
