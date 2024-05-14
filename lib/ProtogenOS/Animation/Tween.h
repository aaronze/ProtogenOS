#pragma once

#include <vector>
#include "KeyFrame.h"
#include "Math/Transform.h"

enum class TweenAnimation {
    Linear
};

class Tween {
private:
    std::vector<std::unique_ptr<KeyFrame>> keyFrames;
    float progress;

public:
    Transform& target;

    explicit Tween(Transform& target) : target(target) {
        progress = 0.0f;
    }

    void clear() {
        keyFrames.clear();
        progress = 0.0f;
    }

    void addKeyFrame(Transform transform, float start = 0.0f, float duration = 1.0f, AnimationStyle animationStyle = AnimationStyle::Linear) {
        auto keyFrame = std::make_unique<KeyFrame>(transform, start, duration, animationStyle);
        keyFrames.push_back(std::move(keyFrame));
    }

    void update(unsigned long delta) {
        progress += float(delta) / 1000.0f;

        Vector3D position = Vector3D(0, 0, 0);
        Vector3D scale = Vector3D(0, 0, 0);
        for (auto& keyFrame : keyFrames) {
            float contribution = keyFrame->getContribution(progress, delta);
            if (contribution == 0.0f) break;

            position += keyFrame->getKeyFrame().getPosition() * contribution;
            scale += keyFrame->getKeyFrame().getScale() * contribution;
        }
        target.setPosition(position);
        target.setScale(scale);
    }
};
