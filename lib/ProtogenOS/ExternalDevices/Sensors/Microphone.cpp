#include "Microphone.h"
#include "ExternalDevices/Teensy.h"

Microphone::Microphone() {
    pin = Teensy::getPin(ExternalDevice::Microphone);

    readings = std::vector<float>(samples);
    frequencies = std::vector<float>(samples / 2);

    analogReadResolution(12);
}

bool Microphone::update() {
    float average = 0;
    for (int i = 0; i < samples; i++) {
        auto value = analogRead(pin);
        readings[i] = value;
        vReal[i] = value;
        vImag[i] = 0;
        average += value;
        delayMicroseconds(1000000 / samplingFrequency);
    }
    average /= samples;

    for (int i = 0; i < samples; i++) {
        auto value = vReal[i] - average;
        if (value < 0) value = 0.0;
        vReal[i] = value;
    }

    return true;
}

std::vector<float>& Microphone::getSamples() {
    return readings;
}

std::vector<float>& Microphone::getFrequencies() {
    FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);
    FFT.compute(FFTDirection::Forward);
    FFT.complexToMagnitude();

    for (int i = 0; i < samples / 2; i++) {
        frequencies[i] = vReal[i] / 10.0f;
    }

    return frequencies;
}

float Microphone::getFrequency() {
    FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);
    FFT.compute(FFTDirection::Forward);
    FFT.complexToMagnitude();

    return FFT.majorPeak();
}
