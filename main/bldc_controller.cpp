#include "bldc_controller.h"
#include <Arduino.h>


BLDCController::BLDCController() {
    motor_pins[0] = 5;
    motor_pins[1] = 6;

    pinMode(motor_pins[0], OUTPUT);
    pinMode(motor_pins[1], OUTPUT);
}

BLDCController::~BLDCController() {};

void BLDCController::setMotorSpeeds(float channel_1, float channel_2) {
    float multiplier = (speed_factor == SPEED_HIGH) ? 0.25 : 0.1;

    float mL = fmax(-1.0, fmin(1.0, channel_2 + channel_1));
    float mR = fmax(-1.0, fmin(1.0, channel_2 - channel_1));

    mL *= multiplier;
    mR *= multiplier;

    int pwmLeft = map((int)(mL * 100), -100, 100, 0, 255); 
    int pwmRight = map((int)(mR * 100), -100, 100, 0, 255);

    analogWrite(motor_pins[0], pwmLeft);
    analogWrite(motor_pins[1], pwmRight);
}

void BLDCController::setSpeedFactor(speedFactor factor) {
    speed_factor = factor;
}