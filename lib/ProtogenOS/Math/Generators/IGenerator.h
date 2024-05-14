#pragma once

class IGenerator {
public:
    virtual ~IGenerator() = default;

    virtual void reset() = 0;
    virtual bool isCompleted() = 0;
    virtual float next(unsigned long delta) = 0;
};
