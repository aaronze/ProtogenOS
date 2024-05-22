#include <Arduino.h>
#include "Faces/Awuff/AwuffController.h"
#include "Faces/Awuff/AwuffFace.h"
#include "ExternalDevices/Displays/HUB75.h"
#include "ExternalDevices/Inputs/ButtonHandler.h"
#include "ExternalDevices/Teensy.h"

std::shared_ptr<IController> controller;
unsigned long previousMillis;

void setup() {
    Teensy::setPin(ExternalDevice::Button, 23);
    Teensy::setPin(ExternalDevice::FanController, 15);

    previousMillis = millis();

    std::shared_ptr<IFace> face = std::make_shared<AwuffFace>();
    std::shared_ptr<IPanel> panel = std::make_shared<HUB75>(255);
    std::shared_ptr<IInput> input = std::make_shared<ButtonHandler>(Teensy::getPin(ExternalDevice::Button));
    controller = std::make_shared<AwuffController>(face, panel, input);

//    std::shared_ptr<IFace> face = std::make_shared<NukudeFace>();
//    std::shared_ptr<IPanel> panel = std::make_shared<HUB75>(120);
//    std::shared_ptr<IInput> input = std::make_shared<ButtonHandler>(23);
//    controller = std::make_shared<NukudeController>(face, panel, input);
}

void loop() {
    auto time = millis();
    auto delta = time - previousMillis;
    previousMillis = time;

    controller->update(delta);
}
