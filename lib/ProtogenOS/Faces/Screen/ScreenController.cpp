#include "ScreenController.h"

void ScreenController::update(unsigned long delta) {
    input->update();
    scene->update(delta);
    renderer->render(scene, panel, camera);
}
