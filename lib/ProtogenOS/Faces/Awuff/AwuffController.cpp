#include "AwuffController.h"

#include "Rendering/Effects/Crying.h"
#include "Rendering/Effects/HeartBubbles.h"

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

    if (input->update()) {
        if (input->getCurrentValue() == 12) {
            face->reset();
            face->morph(Morph::HideBlush);
            face->morph(Morph::Love);
            clearEffects();
            addEffect(new HeartBubbles(scene, 20));
        } else if (input->getCurrentValue() == 19) {
            face->reset();
            face->morph(Morph::HideBlush);
            face->morph(Morph::Sad);
            clearEffects();
            addEffect(new Crying(scene, Vector3D(-12, 9, 0), 6));
        } else {
            face->reset();
            face->morph(Morph::HideBlush);
            clearEffects();
        }
    }

    IController::update(delta);
}
