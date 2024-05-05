#include <Arduino.h>
#include "Rendering/Renderer.h"
#include "Rendering/Scene.h"
#include "Faces/AwuffFace.h"
#include "ExternalDevices/Displays/HUB75.h"
#include "ExternalDevices/Inputs/ButtonHandler.h"
#include "Rendering/Effects/HeartBubbles.h"
#include "Rendering/Effects/Crying.h"

auto panel = std::make_unique<HUB75>(100);
Renderer renderer(std::move(panel));

Scene scene;
AwuffFace face;
IEffect* effect;
ButtonHandler buttonHandler(23);

unsigned long previousMillis;
unsigned long blinkCooldown = 30;

void setup() {
    previousMillis = millis();

    renderer.setup();

    scene.addObject(&face);
}

void loop() {
    auto time = millis();
    auto delta = time - previousMillis;
    previousMillis = time;

    face.morph(Morph::HideBlush, 1.0f);

    if (blinkCooldown == 0 && rand() % 100 == 1) {
        face.morph(Morph::Blink, 1.0f);
        blinkCooldown = 30;
    }
    if (blinkCooldown > 0) {
        if (blinkCooldown < 25) face.morph(Morph::Blink, 0.0f);
        blinkCooldown--;
    }

    if (buttonHandler.update()) {
        if (buttonHandler.getCurrentValue() == 12) {
            face.reset();
            face.morph(Morph::HideBlush);
            face.morph(Morph::Love);
            delete effect;
            effect = new HeartBubbles(&scene, 20);
        } else if (buttonHandler.getCurrentValue() == 19) {
            face.reset();
            face.morph(Morph::HideBlush);
            face.morph(Morph::Sad);
            delete effect;
            effect = new Crying(&scene, 6);
        } else {
            face.reset();
            face.morph(Morph::HideBlush);
            delete effect;
            effect = nullptr;
        }
    }

    if (effect) {
        effect->update(delta);
    }

    scene.update();

    renderer.render(&scene);
}