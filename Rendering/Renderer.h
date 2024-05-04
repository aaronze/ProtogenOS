#pragma once

#include <memory>
#include "ExternalDevices/Displays/IPanel.h"
#include "Rendering/Scene.h"

class Renderer {
private:
    std::unique_ptr<IPanel> panel_;

public:
    explicit Renderer(std::unique_ptr<IPanel> panel)
        : panel_(std::move(panel)) {}

    void setup();
    void render(Scene* scene);
};
