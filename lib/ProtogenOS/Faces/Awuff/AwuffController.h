#pragma once

#include "Faces/IController.h"

class AwuffController : public IController {
private:
    unsigned long blinkCooldown = 30;

public:
    AwuffController(IFace* face, IPanel* panel, IInput* input) : IController(face, panel, input) {}

    void update(unsigned long delta) override;
};
