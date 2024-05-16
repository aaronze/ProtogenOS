#pragma once

#include <algorithm>
#include <vector>
#include "Object.h"
#include "Rendering/UI/IUI.h"

class Scene {
private:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<IUI>> ui;

public:
    virtual ~Scene() = default;

    virtual void update(unsigned long delta) {
        for (auto& obj: objects) {
            obj->update(delta);
        }
    }

    void clear() {
        objects.clear();
    }

    void addObject(const std::shared_ptr<Object>& obj) {
        objects.push_back(obj);
    }

    void removeObject(const std::shared_ptr<Object>& obj) {
        objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
    }

    void clearUI() {
        ui.clear();
    }

    void addUI(std::shared_ptr<IUI>& element) {
        ui.push_back(element);
    }

    void removeUI(std::shared_ptr<IUI>& element) {
        ui.erase(std::remove(ui.begin(), ui.end(), element), ui.end());
    }

    virtual std::vector<std::shared_ptr<Object>> getObjects() {
        return objects;
    }

    virtual std::vector<std::shared_ptr<IUI>> getUI() {
        return ui;
    }
};
