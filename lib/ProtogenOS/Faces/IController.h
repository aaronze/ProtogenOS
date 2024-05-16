#pragma once

#include <vector>
#include "ExternalDevices/Displays/IPanel.h"
#include "ExternalDevices/Inputs/IInput.h"
#include "IFace.h"
#include "Rendering/Effects/IEffect.h"
#include "Rendering/Scene.h"
#include "Rendering/Renderer.h"
#include "Scenes/Menu.h"

class IController {
private:
    float menuCooldown;

protected:
    std::shared_ptr<IFace> face;
    std::shared_ptr<IPanel> panel;
    std::shared_ptr<IInput> input;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Menu> menu;
    std::vector<std::shared_ptr<IEffect>> effects;

    void showMenu() {
        scene = menu;
        menu->showMenu(0.5f);
    }

    void hideMenu() {
        menuCooldown = 0.5f;
        menu->hideMenu(0.5f);
    }

public:
    IController(std::shared_ptr<IFace>& face, std::shared_ptr<IPanel>& panel, std::shared_ptr<IInput>& input)
      : face(face), panel(panel), input(input) {
        this->panel->setup();

        scene = std::make_shared<Scene>();
        scene->addObject(this->face);

        camera = std::make_shared<Camera>();
        renderer = std::make_shared<Renderer>();
        menu = std::make_shared<Menu>(scene);
    }

    virtual ~IController() = default;

    virtual void update(unsigned long delta) {
        if (menuCooldown > 0.0f) {
            menuCooldown -= float(delta) / 1000.0f;
            if (menuCooldown < 0) {
                menuCooldown = 0.0f;
                scene = menu->getPreview();
            }
        }

        size_t deadCount = 0;
        for (auto& effect: effects) {
            if (effect) {
                if (effect->isAlive()) {
                    effect->update(delta);
                } else {
                    effect = nullptr;
                }
            } else {
                deadCount++;
            }
        }

        if (deadCount > 20) {
            effects.erase(std::remove(effects.begin(), effects.end(), nullptr), effects.end());
        }

        scene->update(delta);
        renderer->render(scene, panel, camera);
    }

    void addEffect(const std::shared_ptr<IEffect>& effect) {
        effects.push_back(effect);
    }

    void clearEffects() {
        effects.clear();
    }

    std::shared_ptr<Camera> getCamera() {
        return camera;
    }

    std::shared_ptr<Renderer> getRenderer() {
        return renderer;
    }

    void toggleMenu() {
        if (menuCooldown > 0) {
            menuCooldown = 0.0f;
            showMenu();
        } else if (scene == menu) {
            hideMenu();
        } else {
            showMenu();
        }
    }

    bool handleMenu() {
        auto command = input->getCurrentValue();

        if (scene == menu) {
            switch(command) {
                case 20: toggleMenu(); return true;
            }
        } else if (command == 20) {
            toggleMenu();
            return true;
        }

        return false;
    }
};
