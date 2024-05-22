#pragma once

#include "Faces/IController.h"

class NukudeController : public IController {
public:
    NukudeController(std::shared_ptr<IFace>& face, std::shared_ptr<IPanel>& panel, std::shared_ptr<IInput>& input) : IController(face, panel, input) {
        camera->position = Vector3D(0.0f, 0.0f, -2.5f);
        camera->cameraType = CameraType::Perspective;
        camera->fov = 43.5f;
    }

    void update(unsigned long delta) override;
};
