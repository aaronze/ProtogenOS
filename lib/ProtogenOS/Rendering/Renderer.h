#pragma once

#include <memory>
#include <utility>
#include "ExternalDevices/Displays/IPanel.h"
#include "Camera.h"
#include "Scene.h"
#include "UI/Text2D.h"

class Renderer {
private:
    Text2D debugText = Text2D("", Vector2D(0, 0), 0x00FF00);

public:
    void debug(std::string string) {
        debugText.setText(std::move(string));
    }

    void render(std::shared_ptr<Scene>& scene, std::shared_ptr<IPanel>& panel, std::shared_ptr<Camera>& camera);
};
