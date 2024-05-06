#include <string>
#include "Renderer.h"
#include "Math/Triangle.h"

void Renderer::render(Scene* scene, IPanel* panel) {
    auto objects = scene->getObjects();
    auto width = panel->width();
    auto height = panel->height();

    panel->clear();

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            Vector3D rayOrigin((float)x - width/2, (float)y - height/2, -100.0f);
            Vector3D rayDirection(0, 0, 1.0f);

            Vector3D intersection;
            Vector2D color;
            for (auto& object : objects) {
                if (!object->getMesh()->getBoundingBox()->intersects(rayOrigin, rayDirection)) continue;

                for (auto &triangle: object->getMesh()->getTriangles()) {
                    if (triangle->intersects(rayOrigin, rayDirection, &intersection, &color)) {
                        panel->setPixel(width - x - 1, y, object->getMaterial()->getColor(
                                {(float) x / (float) width, (float) y / (float) height, 0}, triangle->normal, color));
                        panel->setPixel(x, y + height, object->getMaterial()->getColor(
                                {(float) x / (float) width, (float) y / (float) height, 0}, triangle->normal, color));
                    }
                }
            }
        }
    }

    if (!debugString.empty()) {
        panel->drawString(0, 0, 0x00FF00, debugString);
    }

    panel->display();
}
