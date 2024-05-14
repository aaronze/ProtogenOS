#pragma once

#include "Rendering/Scene.h"
#include "Animation/Tween.h"

class Menu : public Scene {
private:
    Scene* preview;
    Transform transform;
    std::unique_ptr<Tween> animation;

public:
    explicit Menu(Scene* preview) : preview(preview) {
        animation = std::make_unique<Tween>(transform);
    }

    void showMenu() {
        animation->clear();
        animation->addKeyFrame(transform, 0.0f, 0.0f);
        animation->addKeyFrame(KeyFrame::fromMove(0.4f, 0.2f, 0.0f), 0.0f, 0.5f);
        animation->addKeyFrame(KeyFrame::fromScale(-0.5f, -0.5f, -0.5f), 0.0f, 0.5f);
    }

    void hideMenu() {
        animation->clear();
        animation->addKeyFrame(transform, 0.0f, 0.0f);
        animation->addKeyFrame(KeyFrame::fromMove(-0.4f, -0.2f, 0.0f), 0.0f, 0.5f);
        animation->addKeyFrame(KeyFrame::fromScale(0.5f, 0.5f, 0.5f), 0.0f, 0.5f);
    }

    Scene* getPreview() {
        return preview;
    }

    std::vector<Object*> getObjects() override {
        return preview->getObjects();
    }

    void update(unsigned long delta) override {
        animation->update(delta);

        for (auto obj: preview->getObjects()) {
            obj->update(delta);
            obj->getMesh()->applyTransform(transform);
        }
    }
};
