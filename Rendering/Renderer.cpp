#include "Renderer.h"
#include "Math/Triangle.h"

void Renderer::setup() {
    panel_->setup();
}

void Renderer::render() {
    Triangle triangle({10, 10, 0}, {20, 20, 0}, {15, 30, 0});

    for (uint16_t y = 0; y < panel_->height(); y++) {
        for (uint16_t x = 0; x < panel_->width(); x++) {
            Vector3D rayOrigin((float)x, (float)y, -1.0f);
            Vector3D rayDirection(0, 0, 1.0f);

            Vector3D intersection;
            Vector2D color;
            if (triangle.intersects(rayOrigin, rayDirection, &intersection, &color)) {
                auto r = (uint8_t)(color.x * 255);
                auto b = (uint8_t)(color.y * 255);

                panel_->setPixel(x, y, (r << 16) | b);
            }
        }
    }

    panel_->display();
}
