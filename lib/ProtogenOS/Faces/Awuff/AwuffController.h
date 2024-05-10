#pragma once

#include "Faces/IController.h"
#include "ExternalDevices/Sensors/BoopSensor.h"

class AwuffController : public IController {
private:
    unsigned long blinkCooldown = 30;
    bool isBooped = false;

    void selectFace();
    void angry();
    void sad();
    void love();

public:
    AwuffController(IFace* face, IPanel* panel, IInput* input) : IController(face, panel, input) {
        BoopSensor::begin(5);
    }

    void update(unsigned long delta) override;
};
