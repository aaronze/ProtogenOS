#pragma once

#include <string>
#include "Math/Vector2D.h"
#include "ExternalDevices/Displays/IPanel.h"

class Text2D {
private:
    std::string text;
    Vector2D position;
    unsigned int color;

public:
    Text2D(const std::string text, const Vector2D position, unsigned int color) : text(text), position(position), color(color) {}

    void setText(const std::string text) {
        this->text = text;
    }

    void setPosition(const Vector2D position) {
        this->position = position;
    }

    void setColor(unsigned int color) {
        this->color = color;
    }

    void render(IPanel* panel) {
        panel->drawString(position.x, position.y, color, text);
    }
};
