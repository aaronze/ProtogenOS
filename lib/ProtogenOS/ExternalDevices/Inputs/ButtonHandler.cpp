#include <algorithm>
#include "ButtonHandler.h"
#include "ExternalDevices/Teensy.h"

ButtonHandler::ButtonHandler() {
    pin = Teensy::getPin(ExternalDevice::Button);
    pinMode(pin, INPUT_PULLUP);

    previousMillis = millis();
    previousState = false;
    currentValue = 0;
    inputCount = 0;
}

bool ButtonHandler::update() {
    bool pinState = !digitalRead(pin);
    long timeOn = millis() - previousMillis;
    if (timeOn < 25) return false;

    if (!pinState && inputCount > 0 && timeOn > 500) {
        uint32_t mask = 0;
        if (inputStream[0] > 0) mask |= (inputStream[0] < 150 ? 1 : 2) << 0; // 1 2
        if (inputStream[1] > 0) mask |= (inputStream[1] < 150 ? 1 : 2) << 2; // 4 8
        if (inputStream[2] > 0) mask |= (inputStream[2] < 150 ? 1 : 2) << 4; // 16 32
        if (inputStream[3] > 0) mask |= (inputStream[3] < 150 ? 1 : 2) << 6; // 64 128

        uint8_t val;
        switch (mask) {
            case 9:   val = 1;  break; // A: .-
            case 86:  val = 2;  break; // B: -...
            case 102: val = 3;  break; // C: -.-.
            case 22:  val = 4;  break; // D: -..
            case 1:   val = 5;  break; // E: .
            case 101: val = 6;  break; // F: ..-.
            case 26:  val = 7;  break; // G: --.
            case 85:  val = 8;  break; // H: ....
            case 5:   val = 9;  break; // I: ..
            case 169: val = 10; break; // J: .---
            case 38:  val = 11; break; // K: -.-
            case 89:  val = 12; break; // L: .-..
            case 10:  val = 13; break; // M: --
            case 6:   val = 14; break; // N: -.
            case 42:  val = 15; break; // O: ---
            case 105: val = 16; break; // P: .--.
            case 154: val = 17; break; // Q: --.-
            case 25:  val = 18; break; // R: .-.
            case 21:  val = 19; break; // S: ...
            case 2:   val = 20; break; // T: -
            case 37:  val = 21; break; // U: ..-
            case 149: val = 22; break; // V: ...-
            case 41:  val = 23; break; // W: .--
            case 150: val = 24; break; // X: -..-
            case 166: val = 25; break; // Y: -.--
            case 90:  val = 26; break; // Z: --..
            default:  val =  0; break;
        }
        currentValue = val;

        std::fill_n(inputStream, inputCount, 0);
        inputCount = 0;
        previousState = false;
        return true;
    }

    if (pinState == previousState) return false;

    if (!pinState && inputCount < 4) {
        inputStream[inputCount] = timeOn;
        inputCount += 1;
    }

    previousMillis = millis();
    previousState = pinState;
    return false;
}


short ButtonHandler::getCurrentValue() {
    return currentValue;
}
