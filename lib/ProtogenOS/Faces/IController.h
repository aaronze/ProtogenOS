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
    IFace* face;
    IInput* input;
    IPanel* panel;
    Scene* scene;
    Renderer* renderer;
    Camera* camera;
    Menu* menu;
    std::vector<IEffect*> effects;

    void showMenu() {
        scene = menu;
        menu->showMenu();
    }

    void hideMenu() {
        menuCooldown = 0.5f;
        menu->hideMenu();
    }

public:
    IController(IFace* face, IPanel* panel, IInput* input) {
        this->face = face;
        this->panel = panel;
        this->input = input;

        this->panel->setup();

        scene = new Scene();
        scene->addObject(face);

        camera = new Camera();
        renderer = new Renderer();
        menu = new Menu(scene);
    }

    ~IController() {
        delete face;
        delete panel;
        delete input;
        delete scene;
        delete camera;
        delete renderer;
        delete menu;
    }

    virtual void update(unsigned long delta) {
        if (menuCooldown > 0.0f) {
            menuCooldown -= float(delta) / 1000.0f;
            if (menuCooldown < 0) {
                menuCooldown = 0.0f;
                scene = menu->getPreview();
            }
        }

        size_t deadCount = 0;
        for (auto &effect: effects) {
            if (effect) {
                if (effect->isAlive()) {
                    effect->update(delta);
                } else {
                    delete effect;
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

    void addEffect(IEffect* effect) {
        effects.push_back(effect);
    }

    void clearEffects() {
        for (auto effect : effects) {
            delete effect;
        }
        effects.clear();
    }

    Camera* getCamera() {
        return camera;
    }

    Renderer* getRenderer() {
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
