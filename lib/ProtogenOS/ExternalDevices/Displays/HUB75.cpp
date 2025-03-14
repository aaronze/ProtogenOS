#include "HUB75.h"

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

const uint32_t letters[36] = {0x1DF6D, 0x35F6F, 0x1C927, 0x35B6E, 0x3CD27, 0x1CD24, 0x1C96F, 0x2DF6D, 0x3A497, 0x3924E, 0x2DD6D, 0x24927, 0x3D5AD6B1, 0x35B6D, 0x1DB6E, 0x3DD24, 0x1DB71, 0x3DD6D, 0x1CE4E, 0x3A492, 0x2DB6F, 0x2DB6A, 0x235AD6AA, 0x2D4AD, 0x2DA92, 0x394A7, 0x1DB6E, 0x16497, 0x312A7, 0x31C4E, 0x2D649, 0x3CC4E, 0x1CD6B, 0x39292, 0x1D56E, 0x35ACE};

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

uint8_t HUB75::getBrightness() {
    return brightness;
}

void HUB75::setBrightness(uint8_t newBrightness) {
    brightness = newBrightness;
    matrix.setBrightness(brightness);
}

void HUB75::setPixel(uint16_t x, uint16_t y, uint32_t color) {
    backgroundLayer.drawPixel(x, y, colorToRGB(color));
}

void HUB75::fill(uint32_t color) {
    backgroundLayer.fillScreen(colorToRGB(color));
}

void HUB75::clear() {
    backgroundLayer.fillScreen(colorToRGB(0));
}

void HUB75::drawString(uint16_t x, uint16_t y, uint32_t color, const std::string& string) {
    for (size_t i = 0; i < string.length(); i++) {
        if (string[i] == ' ') {
            x += 3;
            continue;
        }

        uint32_t charCode = string[i] - 'A';
        uint32_t numCode = string[i] - '0';
        uint32_t letter = letters[numCode < 10 ? 26 + numCode: charCode];

        auto width = (charCode == 12 || charCode == 22) ? 5 : 3;
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 6; k++) {
                if ((letter >> (k * width + j)) & 0x1) {
                    backgroundLayer.drawPixel(x + (width - j), y + (5 - k), colorToRGB(color));
                }
            }
        }
        x += width + 1;
    }
}

uint16_t HUB75::getStringWidth(const std::string& string) {
    uint16_t width = 0;

    for (size_t i = 0; i < string.length(); i++) {
        switch (string[i]) {
            case 'W':
            case 'M':
                width += 5;
            default:
                width += 3;
        }
    }

    width += string.length() - 1;

    return width;
}
