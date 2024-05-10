#pragma once

#include "Faces/IController.h"

class NukudeController : public IController {
public:
    NukudeController(IFace* face, IPanel* panel, IInput* input) : IController(face, panel, input) {
        camera->position = Vector3D(0.0f, 0.0f, -45.0f);
        camera->cameraType = CameraType::Perspective;
        camera->fov = 45.0f;
    }

    void update(unsigned long delta) override;
};
