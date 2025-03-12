#include "ScreenController.h"

void ScreenController::update(unsigned long delta) {
    scene->update(delta);
    renderer->render(scene, panel, camera);
}
