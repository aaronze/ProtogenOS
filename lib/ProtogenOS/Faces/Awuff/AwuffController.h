#pragma once

#include "Faces/IController.h"
#include "ExternalDevices/Sensors/BoopSensor.h"

class AwuffController : public IController {
private:
    bool isBooped = false;
    bool isBlushing = false;
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

public:
    AwuffController(std::shared_ptr<IFace>& face, std::shared_ptr<IPanel>& panel, std::shared_ptr<IInput>& input) : IController(face, panel, input) {
        BoopSensor::begin(5);
        face->setBlinkRate(0.01f);
    }

    void update(unsigned long delta) override;
};
