#pragma once

#include <memory>
#include <utility>
#include "ExternalDevices/Displays/IPanel.h"
#include "Rendering/Scene.h"

class Renderer {
private:
    std::unique_ptr<IPanel> panel_;
    std::string debugString;

public:
    explicit Renderer(std::unique_ptr<IPanel> panel) : panel_(std::move(panel)) {}

    void debug(std::string string) {
        debugString = std::move(string);
    }

    void setup();
    void render(Scene* scene);
};
