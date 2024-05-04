#include <string>
#include "Renderer.h"
#include "Math/Triangle.h"
#include "Faces/AwuffFace.h"

AwuffFace face;

void Renderer::setup() {
    panel_->setup();
}

void Renderer::render() {
    auto object = face.getObject();
    auto triangles = object->getMesh()->getTriangles();
    auto width = panel_->width();
    auto height = panel_->height();

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            Vector3D rayOrigin((float)x - width/2, (float)y - height/2, -100.0f);
            Vector3D rayDirection(0, 0, 1.0f);

            Vector3D intersection;
            Vector2D color;
            for (auto& triangle : triangles) {
                if (triangle->intersects(rayOrigin, rayDirection, &intersection, &color)) {
                    panel_->setPixel(width - x - 1, y, object->getMaterial()->getColor({(float)x/(float)width, (float)y/(float)height, 0}, triangle->normal, color));
                    panel_->setPixel(x, y + height, object->getMaterial()->getColor({(float)x/(float)width, (float)y/(float)height, 0}, triangle->normal, color));
                }
            }
        }
    }

    panel_->display();
}
