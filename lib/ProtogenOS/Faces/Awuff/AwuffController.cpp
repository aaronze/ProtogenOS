#include "AwuffController.h"

#include "Rendering/Effects/Crying.h"
#include "Rendering/Effects/HeartBubbles.h"
#include "Rendering/Materials/SolidMaterial.h"

SolidMaterial Purple(0xFF00FF);
SolidMaterial Red(0xFF0000);

void AwuffController::update(unsigned long delta) {
    face->morph(Morph::HideBlush, 1.0f);

    if (blinkCooldown == 0 && rand() % 100 == 1) {
        face->morph(Morph::Blink, 1.0f);
        blinkCooldown = 30;
    }
    if (blinkCooldown > 0) {
        if (blinkCooldown < 25) face->morph(Morph::Blink, 0.0f);
        blinkCooldown--;
    }

    selectFace();

    IController::update(delta);
}

void AwuffController::selectFace() {
    bool hasInput = input->update();
    if (!hasInput) return;

    face->setMaterial(&Purple);
    face->reset();
    face->morph(Morph::HideBlush);
    clearEffects();

    switch (input->getCurrentValue()) {
        case 1: angry();        break; // [A]ngry
        case 12: love();        break; // [L]ove
        case 19: sad();         break; // [S]ad
    }
}

void AwuffController::angry() {
    face->setMaterial(&Red);
    face->morph(Morph::Anger);
}

void AwuffController::sad() {
    face->morph(Morph::Sad);

    addEffect(new Crying(scene, Vector3D(-12, 9, 0), 6));
}

void AwuffController::love() {
    face->morph(Morph::Love);

    addEffect(new HeartBubbles(scene, 20));
}
