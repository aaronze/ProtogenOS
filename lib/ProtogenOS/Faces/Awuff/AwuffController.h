#pragma once

#include "Faces/IController.h"
#include "ExternalDevices/Sensors/BoopSensor.h"

class AwuffController : public IController {
private:
    unsigned long blinkCooldown = 30;
    bool isBooped = false;
    std::shared_ptr<IMaterial> currentMaterial;

    void selectFace();
    void angry();
    void sad();
    void love();

public:
    AwuffController(std::shared_ptr<IFace>& face, std::shared_ptr<IPanel>& panel, std::shared_ptr<IInput>& input) : IController(face, panel, input) {
        BoopSensor::begin(5);
        currentMaterial = face->getMaterial();
    }

    void update(unsigned long delta) override;
};
