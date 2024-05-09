#pragma once

#include <vector>
#include "ExternalDevices/Displays/IPanel.h"
#include "ExternalDevices/Inputs/IInput.h"
#include "IFace.h"
#include "Rendering/Effects/IEffect.h"
#include "Rendering/Scene.h"
#include "Rendering/Renderer.h"

class IController {
protected:
    IFace* face;
    IInput* input;
    IPanel* panel;
    Scene* scene;
    Renderer* renderer;
    std::vector<IEffect*> effects;

public:
    IController(IFace* face, IPanel* panel, IInput* input) {
        this->face = face;
        this->panel = panel;
        this->input = input;

        this->panel->setup();

        scene = new Scene();
        scene->addObject(face);

        renderer = new Renderer();
    }

    ~IController() {
        delete face;
        delete panel;
        delete input;
        delete scene;
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

        scene->update();
        renderer->render(scene, panel);
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
};
