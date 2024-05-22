#pragma once

#include <string>
#include "EEPROM.h"

class IMenuItem : public IUI {
protected:
    int index;
    std::string text;
    uint8_t value;

public:
    IMenuItem(int index, std::string text) : index(index), text(std::move(text)) {
        value = EEPROM.read(index);
    }

    virtual ~IMenuItem() = default;

    virtual void setValue(uint8_t val) {
        value = val;
        EEPROM.write(index, val);
    }

    virtual uint8_t getValue() {
        return value;
    }
};
