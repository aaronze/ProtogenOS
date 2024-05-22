#include "AwuffController.h"

#include "Rendering/Effects/Crying.h"
#include "Rendering/Effects/HeartBubbles.h"

void AwuffController::update(unsigned long delta) {
    if (blinkCooldown == 0 && rand() % 100 == 1) {
        face->morph(Morph::Blink, 1.0f);
        blinkCooldown = 30;
    } else if (blinkCooldown > 0) {
        if (blinkCooldown < 25) face->morph(Morph::Blink, 0.0f);
        blinkCooldown--;
    }

    if (BoopSensor::isBooped()) {
        face->blendMaterial(Rainbow);
        face->morph(Morph::Happy);
        isBooped = true;
        isBlushing = true;
    } else if (isBooped) {
        face->blendMaterial(currentMaterial);
        face->morph(Morph::Happy, 0.0f);
        isBooped = false;
        isBlushing = false;
    }

    bool hasInput = input->update();
    if (hasInput) {
        if (!handleMenu()) {
            selectFace(input->getCurrentValue());
        }
    }

    face->morph(Morph::HideBlush, isBlushing ? 0.0f : 1.0f, true);
    IController::update(delta);
}

void AwuffController::selectFace(short index) {
    clearEffects();

    face->reset();
    face->blendMaterial(currentMaterial);
    isBlushing = false;

    switch (index) {
        case 1:  angry();       break; // [A]ngry
        case 2: blush();        break; // [B]lush
        case 5:  next();        break; // N[e]xt
//        case 8:  happy();       break; // [H]appy
        case 12: love();        break; // [L]ove
        case 14: angry();       break; // Angry backup
        case 15: surprised();   break; // [O]surprised
        case 18: love();         break; // Love backup
        case 19: sad();         break; // [S]ad
    }
}

void AwuffController::angry() {
    face->blendMaterial(Red);
    face->morph(Anger);
}

void AwuffController::sad() {
    face->morph(Sad);

    addEffect(std::make_shared<Crying>(scene, Vector3D(-0.4f, 0.5f, 0), 6));
}

void AwuffController::love() {
    face->morph(Love);

    addEffect(std::make_shared<HeartBubbles>(scene, 30));
}

void AwuffController::surprised() {
    face->morph(Surprised);
}

void AwuffController::happy() {
    face->morph(Happy);
}

void AwuffController::blush() {
    face->morph(Happy);
    isBlushing = true;
}

void AwuffController::next() {
    currentFace++;
    selectFace(faces[currentFace % 5]);
}
