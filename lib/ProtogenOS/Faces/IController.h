#pragma once

#include <vector>
#include "ExternalDevices/Displays/IPanel.h"
#include "ExternalDevices/Inputs/IInput.h"
#include "ExternalDevices/Outputs/FanController.h"
#include "ExternalDevices/Teensy.h"
#include "IFace.h"
#include "Rendering/Effects/IEffect.h"
#include "Rendering/Scene.h"
#include "Rendering/Materials/RainbowSpiral.h"
#include "Rendering/Materials/SolidMaterial.h"
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

    std::shared_ptr<SolidMaterial> Red = std::make_shared<SolidMaterial>(0xFF0000);
    std::shared_ptr<SolidMaterial> Green = std::make_shared<SolidMaterial>(0x00FF00);
    std::shared_ptr<SolidMaterial> Blue = std::make_shared<SolidMaterial>(0x0000FF);
    std::shared_ptr<SolidMaterial> Purple = std::make_shared<SolidMaterial>(0xFF00FF);
    std::shared_ptr<SolidMaterial> Orange = std::make_shared<SolidMaterial>(0xFFFF00);
    std::shared_ptr<SolidMaterial> Cyan = std::make_shared<SolidMaterial>(0x00FFFF);
    std::shared_ptr<SolidMaterial> White = std::make_shared<SolidMaterial>(0xFFFFFF);
    std::shared_ptr<RainbowSpiral> Rainbow = std::make_shared<RainbowSpiral>(0.8f, Vector2D(10.0f, 10.0f), 1.0f, 0.004f);
    std::shared_ptr<IMaterial> FaceMaterials[10] = {
            Red, Green, Blue, Purple, Orange, Cyan, White, Rainbow, Rainbow, Rainbow
    };
    std::shared_ptr<IMaterial> currentMaterial;

    std::unique_ptr<FanController> fanController;

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
        renderer = std::make_shared<Renderer>(panel->width(), panel->height());
        menu = std::make_shared<Menu>(scene);
        face->setMaterial(FaceMaterials[menu->getMenuValue(Menus::Color)]);
        currentMaterial = face->getMaterial();

        if (Teensy::hasPin(ExternalDevice::FanController)) {
            fanController = std::make_unique<FanController>(Teensy::getPin(ExternalDevice::FanController));
        }
    }

    virtual ~IController() = default;

    virtual void update(unsigned long delta) {
        auto material = FaceMaterials[menu->getMenuValue(Menus::Color)];
        if (currentMaterial != material) {
            face->blendMaterial(material);
            currentMaterial = material;
        }

        uint8_t newBrightness = (menu->getMenuValue(Menus::Brightness) + 1) * 50;
        if (newBrightness != panel->getBrightness()) {
            panel->setBrightness(newBrightness);
        }

        if (fanController) {
            fanController->setPWM(menu->getMenuValue(Menus::FanSpeed) * 64);
        }

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
                case 5: menu->nextOption(); return true; // Short Press
                case 9: menu->prevOption(); return true; // Double Short Press
                case 13: toggleMenu(); return true; // Double Long Press (Exit Menu)
                case 20: menu->nextMenu(); return true; // Long Press
            }
        } else if (command == 20) {
            toggleMenu();
            return true;
        }

        return false;
    }
};
