#include "Renderer.h"
#include "Math/Triangle.h"
#include "Object.h"
#include "Rendering/Materials/SolidMaterial.h"

SolidMaterial material(0xFFFF00);
Object object(&material);

void Renderer::setup() {
    panel_->setup();

    auto t1 = std::make_shared<Triangle>(Vector3D{10, 10, 0}, Vector3D{20, 20, 0}, Vector3D{15, 30, 0});
    auto t2 = std::make_shared<Triangle>(Vector3D{30, 10, 0}, Vector3D{40, 10, 0}, Vector3D{35, 25, 0});
    object.addTriangle(t1);
    object.addTriangle(t2);
}

void Renderer::render() {
    auto triangles = object.getTriangles();
    for (uint16_t y = 0; y < panel_->height(); y++) {
        for (uint16_t x = 0; x < panel_->width(); x++) {
            Vector3D rayOrigin((float)x, (float)y, -1.0f);
            Vector3D rayDirection(0, 0, 1.0f);

            Vector3D intersection;
            Vector2D color;
            for (auto & triangle : triangles) {
                if (triangle->intersects(rayOrigin, rayDirection, &intersection, &color)) {
                    panel_->setPixel(x, y, object.getMaterial()->getColor({(float)x, (float)y, 0}, triangle->normal, color));
                }
            }
        }
    }

    panel_->display();
}
