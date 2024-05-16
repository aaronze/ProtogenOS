#pragma once

#include <vector>
#include "Animation/Tween.h"
#include "Rendering/Scene.h"
#include "UI/Menu/NumberPicker.h"

class Menu : public Scene {
private:
    Transform transform;
    std::shared_ptr<Scene> preview;
    std::unique_ptr<Tween> animation;
    std::vector<std::unique_ptr<IMenuItem>> menuItems;

public:
    explicit Menu(std::shared_ptr<Scene> preview) : preview(std::move(preview)) {
        animation = std::make_unique<Tween>(transform);

        menuItems.push_back(std::make_unique<NumberPicker>(0, "COLOR", 9));
    }

    void showMenu(float duration = 0.5f) {
        animation->clear();
        animation->addKeyFrame(transform, 0.0f, 0.0f);
        animation->addKeyFrame(KeyFrame::fromMove(0.4f, 0.2f, 0.0f), 0.0f, duration, AnimationStyle::ElasticOut);
        animation->addKeyFrame(KeyFrame::fromScale(-0.5f, -0.5f, -0.5f), 0.0f, duration, AnimationStyle::ElasticOut);
    }

    void hideMenu(float duration = 0.5f) {
        animation->clear();
        animation->addKeyFrame(transform, 0.0f, 0.0f);
        animation->addKeyFrame(KeyFrame::fromMove(-0.4f, -0.2f, 0.0f), 0.0f, duration, AnimationStyle::ElasticOut);
        animation->addKeyFrame(KeyFrame::fromScale(0.5f, 0.5f, 0.5f), 0.0f, duration, AnimationStyle::ElasticOut);
    }

    std::shared_ptr<Scene> getPreview() {
        return preview;
    }

    std::vector<std::shared_ptr<Object>> getObjects() override {
        return preview->getObjects();
    }

    void update(unsigned long delta) override {
        animation->update(delta);

        for (auto& obj: preview->getObjects()) {
            obj->update(delta);
            obj->getMesh()->applyTransform(transform);
        }
    }
};
