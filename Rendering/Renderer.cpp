#include "Renderer.h"

void Renderer::setup() {
    panel_->setup();
}

void Renderer::render() {
    panel_->setPixel(10, 10, 0x00FF00);
    panel_->display();
}
