#pragma once

#include "IMenuItem.h"

class NumberPicker : public IMenuItem {
private:
    uint8_t max;

public:
    NumberPicker(int index, std::string text, uint8_t max) : IMenuItem(index, text), max(max) {}

    void setValue(uint8_t val) override {
        IMenuItem::setValue(val % max);
    }

    uint8_t getValue() override {
        return IMenuItem::getValue() % max;
    }
};
