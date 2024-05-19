#include "Teensy.h"

std::unordered_map<ExternalDevice, unsigned short> Teensy::pinMap = {};

unsigned short Teensy::getPin(const ExternalDevice externalDevice) {
    return pinMap[externalDevice];
}

void Teensy::setPin(const ExternalDevice externalDevice, unsigned short pin) {
    pinMap[externalDevice] = pin;
}
