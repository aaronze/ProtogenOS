#include "HUB75.h"

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

HUB75::HUB75(uint8_t initialBrightness) {
    brightness = initialBrightness;
}

rgb24 HUB75::colorToRGB(uint32_t color) {
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;
    return {r, g, b};
}

void HUB75::setup() {
    matrix.addLayer(&backgroundLayer);
    matrix.begin();
    matrix.setBrightness(brightness);
    matrix.setRefreshRate(240);
}

void HUB75::display() {
    backgroundLayer.swapBuffers();
}

uint16_t HUB75::width() {
    return 64;
}

uint16_t HUB75::height() {
    return 32;
}

void HUB75::setPixel(uint16_t x, uint16_t y, uint32_t color) {
    backgroundLayer.drawPixel(x, y, colorToRGB(color));
}

void HUB75::fill(uint32_t color) {
    backgroundLayer.fillScreen(colorToRGB(color));
}
