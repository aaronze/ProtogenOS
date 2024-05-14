#pragma once

#include <algorithm>
#include <vector>
#include "Object.h"
#include "Rendering/UI/IUI.h"

class Scene {
private:
    std::vector<Object*> objects;
    std::vector<IUI*> ui;

public:
    virtual void update(unsigned long delta) {
        for (auto obj: objects) {
            obj->update(delta);
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

    void clearUI() {
        ui.clear();
    }

    void addUI(IUI* ui) {
        this->ui.push_back(ui);
    }

    void removeUI(IUI* ui) {
        this->ui.erase(std::remove(this->ui.begin(), this->ui.end(), ui), this->ui.end());
    }

    virtual std::vector<Object*> getObjects() {
        return objects;
    }

    virtual std::vector<IUI*> getUI() {
        return ui;
    }
};
