#pragma once

#include <memory>
#include <utility>
#include "ExternalDevices/Displays/IPanel.h"
#include "Camera.h"
#include "Scene.h"

class Renderer {
private:
    std::string debugString;

public:
    void debug(std::string string) {
        debugString = std::move(string);
    }

    void render(Scene* scene, IPanel* panel, Camera* camera);
};
