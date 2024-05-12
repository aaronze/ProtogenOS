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
protected:
    IFace* face;
    IInput* input;
    IPanel* panel;
    Scene* scene;
    Renderer* renderer;
    Camera* camera;
    Menu* menu;
    std::vector<IEffect*> effects;

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

    void showMenu() {
        scene = menu;
    }

    void hideMenu() {
        scene = menu->getPreview();
    }

    bool handleMenu() {
        auto command = input->getCurrentValue();
        if (scene == menu) {
            switch(command) {
                case 20: hideMenu(); return true;
            }
        } else if (command == 20) {
            showMenu();
            return true;
        }

        return false;
    }
};
