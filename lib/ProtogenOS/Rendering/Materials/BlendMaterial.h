#pragma once

#include "IMaterial.h"

class BlendMaterial : public IMaterial {
private:
    std::shared_ptr<IMaterial> fromMaterial {};
    std::shared_ptr<IMaterial> toMaterial {};
    float speed;
    float progress = 0.0f;

public:
    BlendMaterial(std::shared_ptr<IMaterial> from, std::shared_ptr<IMaterial> to, float speed = 0.03f) : fromMaterial(from), toMaterial(to), speed(speed) {};

    float getProgress() {
        return progress;
    }

    std::shared_ptr<IMaterial> getMaterial() {
        return toMaterial;
    }

    uint32_t getColor(const Vector3D& position, const Vector3D& normal, const Vector2D& uv) override {
        if (progress > 0.99f) {
            return toMaterial->getColor(position, normal, uv);
        }

        auto colorFrom = fromMaterial->getColor(position, normal, uv);
        auto colorTo = toMaterial->getColor(position, normal, uv);
        unsigned int r = ((colorFrom >> 16) & 0xFF) * (1.0f - progress) + ((colorTo >> 16) & 0xFF) * progress;
        unsigned int g = ((colorFrom >> 8) & 0xFF) * (1.0f - progress) + ((colorTo >> 8) & 0xFF) * progress;
        unsigned int b = (colorFrom & 0xFF) * (1.0f - progress) + (colorTo & 0xFF) * progress;
        return (r << 16) | (g << 8) | b;
    }

    void update(unsigned long delta) override {
        fromMaterial->update(delta);
        toMaterial->update(delta);

        progress += speed * delta / 30.0f;
        if (progress > 1.0f) progress = 1.0f;
    }
};

