#include "HeartBubbles.h"

HeartBubbles::HeartBubbles(Scene* scene, unsigned int numberOfHearts, unsigned long duration) : IEffect(duration) {
    this->scene = scene;

    for (unsigned int i = 0; i < numberOfHearts; i++) {
        float x = -32 + (64.0f / numberOfHearts) * i;

        auto heart = new Heart();
        heart->getTransform().translate(Vector3D(x + std::rand() % 4, 62 - std::rand() % 40, 0));
        hearts.push_back(heart);
    }

    for (auto heart : hearts) {
        scene->addObject(heart);
    }
}

HeartBubbles::~HeartBubbles() {
    for (auto heart : hearts) {
        scene->removeObject(heart);
        delete heart;
    }
    hearts.clear();
}

void HeartBubbles::update(unsigned long delta) {
    for (auto heart : hearts) {
        auto position = heart->getTransform().getPosition();
        heart->getTransform().translate(Vector3D(position.x, position.y - delta / 30.0f, 0));
    }
}