#include "AwuffController.h"

#include "Rendering/Effects/Crying.h"
#include "Rendering/Effects/HeartBubbles.h"
#include "Rendering/Materials/SolidMaterial.h"
#include "Rendering/Materials/RainbowSpiral.h"

auto Purple = std::make_shared<SolidMaterial>(0xFF00FF);
auto Red = std::make_shared<SolidMaterial>(0xFF0000);
auto Rainbow = std::make_shared<RainbowSpiral>(0.8f, Vector2D(1.0f, 0.0f), 1.0f, 0.03f);

void AwuffController::update(unsigned long delta) {
    face->morph(Morph::HideBlush);

    if (blinkCooldown == 0 && rand() % 100 == 1) {
        face->morph(Morph::Blink, 1.0f);
        blinkCooldown = 30;
    } else if (blinkCooldown > 0) {
        if (blinkCooldown < 25) face->morph(Morph::Blink, 0.0f);
        blinkCooldown--;
    }

    if (BoopSensor::isBooped()) {
        face->morph(Morph::HideBlush, 0.0f);
        face->blendMaterial(Rainbow);
        isBooped = true;
    } else if (isBooped) {
        face->blendMaterial(currentMaterial);
        isBooped = false;
    }

    bool hasInput = input->update();
    if (hasInput) {
        if (!handleMenu()) {
            selectFace();
        }
    }

    IController::update(delta);
}

void AwuffController::selectFace() {
    clearEffects();

    face->reset();
    currentMaterial = Purple;
    face->blendMaterial(currentMaterial);
    face->morph(HideBlush);

    switch (input->getCurrentValue()) {
        case 1: angry();        break; // [A]ngry
        case 12: love();        break; // [L]ove
        case 19: sad();         break; // [S]ad
    }
}

void AwuffController::angry() {
    currentMaterial = Red;
    face->blendMaterial(currentMaterial);
    face->morph(Morph::Anger);
}

void AwuffController::sad() {
    face->morph(Morph::Sad);

    addEffect(new Crying(scene, Vector3D(-0.4f, 0.5f, 0), 6));
}

void AwuffController::love() {
    face->morph(Morph::Love);

    addEffect(new HeartBubbles(scene, 20));
}
