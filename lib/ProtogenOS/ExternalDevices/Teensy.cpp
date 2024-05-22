#include "Teensy.h"

std::unordered_map<ExternalDevice, unsigned short> Teensy::pinMap = {};

bool Teensy::hasPin(const ExternalDevice externalDevice) {
    return pinMap.find(externalDevice) != pinMap.end();
}

unsigned short Teensy::getPin(const ExternalDevice externalDevice) {
    return pinMap[externalDevice];
}

void Teensy::setPin(const ExternalDevice externalDevice, unsigned short pin) {
    pinMap[externalDevice] = pin;
}
