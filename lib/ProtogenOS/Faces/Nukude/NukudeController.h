#pragma once

#include "Faces/IController.h"

class NukudeController : public IController {
public:
    NukudeController(IFace* face, IPanel* panel, IInput* input) : IController(face, panel, input) {}

    void update(unsigned long delta) override;
};
