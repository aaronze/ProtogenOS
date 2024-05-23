#pragma once

#include "Faces/IController.h"

class LEDPowerController : public IController {
public:
    LEDPowerController(std::shared_ptr<IFace>& face, std::shared_ptr<IPanel>& panel, std::shared_ptr<IInput>& input) : IController(face, panel, input) {}

    void update(unsigned long delta) {
        IController::update(delta);
    }
};
