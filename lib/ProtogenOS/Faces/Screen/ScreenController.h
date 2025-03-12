#pragma once

#include "Faces/IController.h"
#include "ExternalDevices/Sensors/BoopSensor.h"

class ScreenController : public IController {
private:
    bool isBooped = false;

public:
    ScreenController(std::shared_ptr<IFace>& face, std::shared_ptr<IPanel>& panel, std::shared_ptr<IInput>& input) : IController(face, panel, input) {
        BoopSensor::begin(5);
    }

    void update(unsigned long delta) override;
};
