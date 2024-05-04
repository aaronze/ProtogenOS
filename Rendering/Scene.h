#pragma once

#include <algorithm>
#include <vector>
#include "Object.h"

class Scene {
private:
    std::vector<Object*> objects;

public:
    void update() {
        for (auto obj: objects) {
            obj->update();
        }
    }

    void clear() {
        objects.clear();
    }

    void addObject(Object* obj) {
        objects.push_back(obj);
    }

    void removeObject(Object* obj) {
        objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
    }

    std::vector<Object*> getObjects() {
        return objects;
    }
};
