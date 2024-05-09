#include "Crying.h"

Crying::Crying(Scene* scene, Vector3D target, unsigned int numberOfTears, unsigned long duration) : IEffect(duration) {
    this->scene = scene;
    this->target = target;

    for (unsigned int i = 0; i < numberOfTears; i++) {
        auto tear = new Tear();
        tear->getTransform().setPosition(Vector3D(target.x + std::rand() % 10 - 5, target.y + std::rand() % 10 - 5, 0));
        tears.push_back(tear);
    }

    for (auto tear : tears) {
        scene->addObject(tear);
    }
}

Crying::~Crying() {
    for (auto tear : tears) {
        scene->removeObject(tear);
        delete tear;
    }
    tears.clear();
}

void Crying::update(unsigned long delta) {
    for (auto tear : tears) {
        auto position = tear->getTransform().getPosition();
        if (position.y > target.y) position.y -= 5.0f;
        tear->getTransform().setPosition(Vector3D(position.x, position.y + delta / 200.0f, 0));
    }
}