
#pragma once

#include <Arduino.h>
#include <arduinoFFT.h>
#include <Wire.h>

class Microphone {
    private:
        static const int samples = 1024; // Must be power of 2 (except 2048 and 4096)
        const float samplingFrequency = 44100;
        unsigned short pin;
        std::vector<float> readings;
        std::vector<float> frequencies;

        float vReal[samples];
        float vImag[samples];

        ArduinoFFT<float> FFT = ArduinoFFT<float>(vReal, vImag, samples, samplingFrequency);

    public:
        explicit Microphone();

        bool update();
        std::vector<float>& getSamples();
        std::vector<float>& getFrequencies();
        float getFrequency();
    };

