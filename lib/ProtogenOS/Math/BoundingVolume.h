#pragma once

#include <memory>
#include <vector>
#include "BoundingBox.h"
#include "Rendering/Object.h"
#include "Vector3D.h"

class BoundingVolume {
public:
    std::shared_ptr<BoundingBox> boundingBox;
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<BoundingVolume>> children;

    explicit BoundingVolume(std::vector<std::shared_ptr<Object>>& objects) {
        Vector3D min = { 9999999, 9999999, 9999999 };
        Vector3D max = { -9999999, -9999999, -9999999 };
        Vector3D median = { 0, 0, 0 };

        for (const auto& object: objects) {
            const auto& objectBoundingBox = object->getMesh()->getBoundingBox();
            min.x = std::min(min.x, objectBoundingBox->min().x);
            min.y = std::min(min.y, objectBoundingBox->min().y);
            min.z = std::min(min.z, objectBoundingBox->min().z);
            max.x = std::max(max.x, objectBoundingBox->max().x);
            max.y = std::max(max.y, objectBoundingBox->max().y);
            max.z = std::max(max.z, objectBoundingBox->max().z);
            median += object->getTransform().getPosition();
        }
        boundingBox = std::make_shared<BoundingBox>(min, max);

        if (objects.size() > 1) {
            median.x /= objects.size();
            median.y /= objects.size();
            median.z /= objects.size();

            Vector3D diff = max - min;
            Vector3D axis;

            if (diff.x >= diff.y && diff.x >= diff.z) {
                axis = {1, 0, 0};
            } else if (diff.y >= diff.x && diff.y >= diff.z) {
                axis = {0, 1, 0};
            } else {
                axis = {0, 0, 1};
            }

            auto pivot = median.dot(axis);
            std::vector<std::shared_ptr<Object>> leftObjects;
            std::vector<std::shared_ptr<Object>> rightObjects;
            for (const auto& object: objects) {
                if (object->getTransform().getPosition().dot(axis) < pivot) {
                    leftObjects.push_back(object);
                } else {
                    rightObjects.push_back(object);
                }
            }

            if (!leftObjects.empty() && !rightObjects.empty()) {
                auto left = std::make_shared<BoundingVolume>(leftObjects);
                auto right = std::make_shared<BoundingVolume>(rightObjects);
                children.push_back(left);
                children.push_back(right);
            }
        } else {
            this->objects = objects;
        }
    }

    bool intersects(const Vector3D& rayOrigin, const Vector3D& rayDirection, std::vector<std::shared_ptr<Object>>* outObjects) const {
        if (!boundingBox->intersects(rayOrigin, rayDirection)) {
            return false;
        }

        if (children.empty()) {
            for (const auto& object : objects) {
                outObjects->push_back(object);
            }
            return true;
        }

        bool hit = false;
        for (const auto& child : children) {
            hit = child->intersects(rayOrigin, rayDirection, outObjects) || hit;
        }
        return hit;
    }
};
