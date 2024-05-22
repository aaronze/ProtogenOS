#pragma once

#include "IMenuItem.h"

class NumberPicker : public IMenuItem {
private:
    uint8_t max;

public:
    NumberPicker(int index, std::string text, uint8_t max) : IMenuItem(index, text), max(max) {}

    void setValue(uint8_t val) override {
        IMenuItem::setValue(val % (max + 1));
    }

    uint8_t getValue() override {
        return IMenuItem::getValue() % (max + 1);
    }

    void render(std::shared_ptr<IPanel>& panel) override {
        uint16_t x = 0;
        panel->drawString(x, 0, 0xFFFFFF, text);
        x += panel->getStringWidth(text) + 2;

        for (size_t i = 0; i <= max; i++) {
            auto digit = std::to_string(i);
            auto color = i == value ? 0x00FF00 : 0x0000FF;

            panel->drawString(x, 0, color, digit);
            x += panel->getStringWidth(digit) + 1;
        }
    }
};
