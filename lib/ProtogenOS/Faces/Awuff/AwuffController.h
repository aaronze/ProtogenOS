#pragma once

#include "Faces/IController.h"
#include "ExternalDevices/Sensors/BoopSensor.h"
#include "ExternalDevices/Outputs/FanController.h"
#include "ExternalDevices/Teensy.h"

class AwuffController : public IController {
private:
    unsigned long blinkCooldown = 30;
    bool isBooped = false;
    bool isBlushing = false;
    std::shared_ptr<IMaterial> currentMaterial;
    short currentFace = 0;
    short faces[5] = {8, 1, 12, 15, 19};

    void selectFace(short index);
    void angry();
    void sad();
    void love();
    void surprised();
    void happy();
    void blush();
    void next();

    FanController fanController;
    float fanSpeed = 0.5f;

public:
    AwuffController(std::shared_ptr<IFace>& face, std::shared_ptr<IPanel>& panel, std::shared_ptr<IInput>& input)
        : IController(face, panel, input), fanController(Teensy::getPin(ExternalDevice::FanController)) {
        BoopSensor::begin(5);
        currentMaterial = face->getMaterial();
    }

    void update(unsigned long delta) override;
};
