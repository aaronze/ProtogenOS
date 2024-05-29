#pragma once

#include <memory>
#include <utility>
#include "Camera.h"
#include "DepthBuffer.h"
#include "ExternalDevices/Displays/IPanel.h"
#include "Scene.h"
#include "UI/Text2D.h"

class Renderer {
private:
    Text2D debugText = Text2D("", Vector2D(0, 0), 0x00FF00);
    DepthBuffer depthBuffer;

public:
    void debug(std::string string) {
        debugText.setText(std::move(string));
    }

    Renderer(size_t width, size_t height) : depthBuffer(width, height) {}

    void render(std::shared_ptr<Scene>& scene, std::shared_ptr<IPanel>& panel, std::shared_ptr<Camera>& camera);
};
