#pragma once

#include "Rendering/Object.h"

class IFace {
public:
    virtual ~IFace() = default;

    virtual Object* getObject() const = 0;
};