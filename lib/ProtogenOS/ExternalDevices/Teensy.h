#pragma once

#include <unordered_map>

enum class ExternalDevice {
    Button,
    FanController,
};

class Teensy {
private:
    static std::unordered_map<ExternalDevice, unsigned short> pinMap;

public:
    static bool hasPin(ExternalDevice externalDevice);

    static unsigned short getPin(ExternalDevice externalDevice);

    static void setPin(ExternalDevice externalDevice, unsigned short pin);
};
