#pragma once

class IInput {
public:
    virtual ~IInput() = default;

    virtual bool update() = 0;
    virtual short getCurrentValue() = 0;
};
