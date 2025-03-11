#pragma once

#include <string>

class IPanel {
public:
    virtual ~IPanel() = default;

    virtual void setup() = 0;
    virtual void display() = 0;

    virtual uint16_t width() = 0;
    virtual uint16_t height() = 0;
    virtual uint8_t getBrightness() = 0;

    virtual void setBrightness(uint8_t newBrightness) = 0;
    virtual void setPixel(uint16_t x, uint16_t y, uint32_t color) = 0;
    virtual void clear() = 0;
    virtual void fill(uint32_t color) = 0;
    virtual void drawString(uint16_t x, uint16_t y, uint32_t color, const std::string& string) = 0;
    virtual uint16_t getStringWidth(const std::string& string) = 0;
};
