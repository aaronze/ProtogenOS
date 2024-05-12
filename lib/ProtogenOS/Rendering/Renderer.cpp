#include <math.h>
#include <string>
#include "Math/Triangle.h"
#include "Renderer.h"

void Renderer::render(Scene* scene, IPanel* panel, Camera* camera) {
    auto objects = scene->getObjects();
    auto width = panel->width();
    auto height = panel->height();

    panel->clear();

    float tanFov = tanf(camera->fov * float(M_PI) / 180.0f / 2.0f);
    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            // Normalise display space to screen space (x: -1..1, y: -1..1)
            float nx = (float(x) / float(width)) * 2.0f - 1.0f;
            float ny = (float(y) / float(height)) * 2.0f - 1.0f;

            Vector3D rayOrigin, rayDirection;
            if (camera->cameraType == CameraType::Perspective) {
                rayOrigin = camera->position;
                rayDirection = (camera->right * nx * tanFov) + (camera->up * ny * tanFov) + camera->forward;
                rayDirection.normalize();
            } else {
                rayOrigin = camera->position + Vector3D(nx, ny, -100.0f);
                rayDirection = camera->forward;
            }

            Vector3D intersection;
            Vector2D color;
            for (auto& object : objects) {
                if (!object->getMesh()->getBoundingBox()->intersects(rayOrigin, rayDirection)) continue;

                for (auto &triangle: object->getMesh()->getTriangles()) {
                    if (triangle->intersects(rayOrigin, rayDirection, &intersection, &color)) {
                        panel->setPixel(width - x - 1, y, object->getMaterial()->getColor(
                                {nx * 2.0f - 1.0f, ny * 2.0f - 1.0f, 0}, triangle->normal, color));
                        panel->setPixel(x, y + height, object->getMaterial()->getColor(
                                {nx * 2.0f - 1.0f, ny * 2.0f - 1.0f, 0}, triangle->normal, color));
                        break;
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
