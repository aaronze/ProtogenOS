#include "Crying.h"

Crying::Crying(Scene* scene, unsigned int numberOfTears, unsigned long duration) : IEffect(duration) {
    this->scene = scene;

    for (unsigned int i = 0; i < numberOfTears; i++) {
        // TODO: Add a targeting vector
        float x = -12;
        float y = 9;

        auto tear = new Tear();
        tear->getTransform().translate(Vector3D(x + std::rand() % 10 - 5, y + std::rand() % 10 - 5, 0));
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
        if (position.y > 9) position.y -= 5.0f;
        tear->getTransform().translate(Vector3D(position.x, position.y + delta / 200.0f, 0));
    }
}