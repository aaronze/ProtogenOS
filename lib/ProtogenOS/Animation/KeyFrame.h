#pragma once

#include "Math/Transform.h"
#include "Math/Generators/LinearGenerator.h"

enum class AnimationStyle {
    Linear
};

class KeyFrame {
private:
    Transform keyFrame;
    float start;
    float end;
    IGenerator* generator;

public:
    explicit KeyFrame(Transform keyFrame, float start = 0.0f, float duration = 1.0f, AnimationStyle animationStyle = AnimationStyle::Linear)
        : keyFrame(keyFrame), start(start), end(start + duration) {
        switch (animationStyle) {
            case AnimationStyle::Linear:
                generator = new LinearGenerator(0.0f, 1.0f, 1.0f / (30.0f * duration));
                break;
        }
    }

    ~KeyFrame() {
        delete generator;
    }

    static Transform fromMove(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
        auto transform = Transform();
        transform.setPosition(Vector3D(x, y, z));
        transform.setScale(Vector3D(0, 0, 0));
        return transform;
    }

    static Transform fromScale(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
        auto transform = Transform();
        transform.setPosition(Vector3D(0, 0, 0));
        transform.setScale(Vector3D(x, y, z));
        return transform;
    }

    float getContribution(float time, unsigned int delta) {
        if (time < start) return 0.0f;
        if (time >= end) return 1.0f;

        return generator->next(delta);
    }

    Transform& getKeyFrame() {
        return keyFrame;
    }
};