#pragma once

class IPanel {
public:
    virtual ~IPanel() = default;

    virtual void setup() = 0;
    virtual void display() = 0;
    virtual void setPixel(int16_t x, int16_t y, uint32_t color) = 0;
};
