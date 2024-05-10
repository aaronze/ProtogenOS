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
            Vector3D rayOrigin, rayDirection;
            if (camera->cameraType == CameraType::Perspective) {
                float nx = (2.0f * ((float(x) + 0.5f) / float(width)) - 1.0f) * tanFov;
                float ny = (2.0f * ((float(y) + 0.5f) / float(height)) - 1.0f) * tanFov;
                rayOrigin = camera->position;
                rayDirection = (camera->right * nx) + (camera->up * ny) + camera->forward;
                rayDirection.normalize();
            } else {
                rayOrigin = camera->position + Vector3D((float)x - width/2, (float)y - height/2, -100.0f);
                rayDirection = camera->forward;
            }

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
