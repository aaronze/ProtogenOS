#include <Arduino.h>
#include "Rendering/Renderer.h"
#include "Rendering/Scene.h"
#include "Faces/AwuffFace.h"
#include "ExternalDevices/Displays/HUB75.h"
#include "ExternalDevices/Inputs/ButtonHandler.h"
#include "Rendering/Effects/HeartBubbles.h"

auto panel = std::make_unique<HUB75>(100);
Renderer renderer(std::move(panel));

Scene scene;
AwuffFace face;
IEffect* effect;
ButtonHandler buttonHandler(23);

unsigned long previousMillis;

void setup() {
    previousMillis = millis();

    renderer.setup();

    scene.addObject(&face);
}

void loop() {
    auto time = millis();
    auto delta = time - previousMillis;
    previousMillis = time;

    if (buttonHandler.update()) {
        face.reset();
        face.morph(Morph::Love);

        delete effect;
        effect = new HeartBubbles(&scene, 20);
    }

    if (effect) {
        effect->update(delta);
    }

    scene.update();

    renderer.render(&scene);
}