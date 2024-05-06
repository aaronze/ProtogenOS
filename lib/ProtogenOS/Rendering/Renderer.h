#pragma once

#include <memory>
#include <utility>
#include "ExternalDevices/Displays/IPanel.h"
#include "Rendering/Scene.h"

class Renderer {
private:
    std::string debugString;

public:
    void debug(std::string string) {
        debugString = std::move(string);
    }

    void render(Scene* scene, IPanel* panel);
};
