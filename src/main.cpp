#include <Arduino.h>
#include "Faces/Awuff/AwuffController.h"
#include "Faces/Awuff/AwuffFace.h"
#include "ExternalDevices/Displays/HUB75.h"
#include "ExternalDevices/Inputs/ButtonHandler.h"

IController* controller;
unsigned long previousMillis;

void setup() {
    previousMillis = millis();

    auto face = new AwuffFace();
    auto panel = new HUB75(120);
    auto input = new ButtonHandler(23);
    controller = new AwuffController(face, panel, input);
}

void loop() {
    auto time = millis();
    auto delta = time - previousMillis;
    previousMillis = time;

    controller->update(delta);
}
