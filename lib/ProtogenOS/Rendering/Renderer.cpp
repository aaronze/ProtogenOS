#include <cmath>
#include <string>
#include <vector>
#include "Math/BoundingVolume.h"
#include "Math/Triangle.h"
#include "Renderer.h"

void Renderer::render(std::shared_ptr<Scene>& scene, std::shared_ptr<IPanel>& panel, std::shared_ptr<Camera>& camera) {
    Vector3D intersection;
    Vector2D color;

    auto objects = scene->getObjects();
    auto width = panel->width();
    auto height = panel->height();

    panel->clear();
    depthBuffer.clear();

    BoundingVolume boundedVolume = BoundingVolume(objects);
    std::vector<std::shared_ptr<Object>> boundedObjects;

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

            boundedObjects.clear();
            boundedVolume.intersects(rayOrigin, rayDirection, &boundedObjects);
            for (auto& object : boundedObjects) {
                for (auto& triangle: object->getMesh()->getTriangles()) {
                    if (triangle->intersects(rayOrigin, rayDirection, &intersection, &color)) {
                        auto distance = (intersection - rayOrigin).lengthSquared();
                        if (!depthBuffer.testDepth(x, y, distance)) continue;
                        depthBuffer.setDepth(x, y, distance);

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

    for (auto& ui : scene->getUI()) {
        ui->render(panel);
    }
    debugText.render(panel);

    panel->display();
}
