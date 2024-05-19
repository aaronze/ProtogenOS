#pragma once

#include <Arduino.h>

class FanController {
private:
    unsigned short pin;
    unsigned short pwm;

public:
    FanController(unsigned short pin) : pin(pin), pwm(128) {
        pinMode(pin, OUTPUT);
    }

    void setPWM(unsigned short pwm) {
        this->pwm = pwm;
        analogWrite(pin, pwm);
    }

    void setSpeed(float speed) {
        if (speed > 1.0f) speed = 1.0f;
        if (speed < 0.0f) speed = 0.0f;
        setPWM((unsigned short)(speed * 255.0f));
    }
};
