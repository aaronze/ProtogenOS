#pragma once

#include <string>
#include "IUI.h"
#include "Math/Vector2D.h"

class Text2D : public IUI {
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

    void render(IPanel* panel) override {
        if (text.empty()) return;

        panel->drawString(position.x, position.y, color, text);
    }
};
