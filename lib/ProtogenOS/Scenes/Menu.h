#pragma once

#include "Rendering/Scene.h"

class Menu : public Scene {
private:
    Scene* preview;
    Transform transform;

public:
    explicit Menu(Scene* preview) : preview(preview) {
        transform.setScale(Vector3D(0.5f, 0.5f, 0.5f));
        transform.setPosition(Vector3D(16, 6, 0));
    }

    Scene* getPreview() {
        return preview;
    }

    std::vector<Object*> getObjects() override {
        return preview->getObjects();
    }

    void update(unsigned long delta) override {
        for (auto obj: preview->getObjects()) {
            obj->update(delta);
            obj->getMesh()->applyTransform(transform);
        }
    }
};
