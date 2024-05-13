#include "HeartBubbles.h"

HeartBubbles::HeartBubbles(Scene* scene, unsigned int numberOfHearts, unsigned long duration) : IEffect(duration) {
    this->scene = scene;

    for (unsigned int i = 0; i < numberOfHearts; i++) {
        float x = -1.0f + (2.0f / numberOfHearts) * i;

        auto heart = new Heart();
        heart->getTransform().setPosition(Vector3D(x + (std::rand() % 4) / 32.0f, 4.0f - (std::rand() % 40) / 16.0f, 0));
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
        heart->getTransform().setPosition(Vector3D(position.x, position.y - delta / 600.0f, 0));
    }
}