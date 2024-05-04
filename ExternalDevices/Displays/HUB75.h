#pragma once

#include <MatrixHardware_Teensy4_ShieldV5.h>
#include <SmartMatrix.h>
#include "IPanel.h"

#define COLOR_DEPTH 24
const uint16_t kMatrixWidth = 64;       // Width of panel
const uint16_t kMatrixHeight = 64;      // Height of panel
const uint8_t kRefreshDepth = 36;
const uint8_t kDmaBufferRows = 4;
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;
const uint32_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

class HUB75 : public IPanel {
private:
    uint8_t brightness;

    static rgb24 colorToRGB(uint32_t color);

public:
    explicit HUB75(uint8_t initialBrightness);

    void setup() override;
    void display() override;

    uint16_t width() override;
    uint16_t height() override;

    void setPixel(uint16_t x, uint16_t y, uint32_t color) override;
    void drawString(uint16_t x, uint16_t y, uint32_t color, const char string[]) override;
    void clear() override;
    void fill(uint32_t color) override;
};
