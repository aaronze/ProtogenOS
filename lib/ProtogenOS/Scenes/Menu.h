#pragma once

#include <vector>
#include "Animation/Tween.h"
#include "Rendering/Scene.h"
#include "UI/Menu/NumberPicker.h"

enum class Menus {
    Color,
    Brightness,
    FanSpeed,
};

class Menu : public Scene {
private:
    Transform transform;
    std::shared_ptr<Scene> preview;
    std::unique_ptr<Tween> animation;
    std::vector<std::shared_ptr<IMenuItem>> menuItems;
    std::shared_ptr<IMenuItem> currentMenuItem;
    size_t menuIndex = 0;

public:
    explicit Menu(std::shared_ptr<Scene> preview) : preview(std::move(preview)) {
        animation = std::make_unique<Tween>(transform);

        menuItems.push_back(std::make_shared<NumberPicker>(int(Menus::Color), "COLOR", 9));
        menuItems.push_back(std::make_shared<NumberPicker>(int(Menus::Brightness), "BRIGHTNESS", 4));
        menuItems.push_back(std::make_shared<NumberPicker>(int(Menus::FanSpeed), "FAN SPEED", 4));
    }

    void showMenu(float duration = 0.5f) {
        animation->clear();
        animation->addKeyFrame(transform, 0.0f, 0.0f);
        animation->addKeyFrame(KeyFrame::fromMove(0.4f, 0.2f, 0.0f), 0.0f, duration, AnimationStyle::ElasticOut);
        animation->addKeyFrame(KeyFrame::fromScale(-0.5f, -0.5f, -0.5f), 0.0f, duration, AnimationStyle::ElasticOut);

        showMenuItem(menuItems.front());
        menuIndex = 0;
    }

    void hideMenu(float duration = 0.5f) {
        if (currentMenuItem) {
            auto menuItemObj = std::shared_ptr<IUI>(currentMenuItem);
            removeUI(menuItemObj);
        }

        animation->clear();
        animation->addKeyFrame(transform, 0.0f, 0.0f);
        animation->addKeyFrame(KeyFrame::fromMove(-0.4f, -0.2f, 0.0f), 0.0f, duration, AnimationStyle::ElasticOut);
        animation->addKeyFrame(KeyFrame::fromScale(0.5f, 0.5f, 0.5f), 0.0f, duration, AnimationStyle::ElasticOut);
    }

    void nextMenu() {
        menuIndex = (menuIndex + 1) % menuItems.size();
        showMenuItem(menuItems[menuIndex]);
    }

    void previousMenu() {
        menuIndex = (menuIndex - 1) % menuItems.size();
        showMenuItem(menuItems[menuIndex]);
    }

    void nextOption() {
        currentMenuItem->setValue(currentMenuItem->getValue() + 1);
    }

    void prevOption() {
        currentMenuItem->setValue(currentMenuItem->getValue() - 1);
    }

    uint8_t getMenuValue(Menus menuItem) {
        return menuItems[int(menuItem)]->getValue();
    }

    void showMenuItem(const std::shared_ptr<IMenuItem>& menuItem) {
        if (currentMenuItem) {
            auto menuItemObj = std::shared_ptr<IUI>(currentMenuItem);
            removeUI(menuItemObj);
        }

        auto menuItemObj = std::shared_ptr<IUI>(menuItem);
        addUI(menuItemObj);

        currentMenuItem = menuItem;
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
