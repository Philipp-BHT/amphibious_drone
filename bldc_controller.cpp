#include "bldc_controller.h"
#include <Arduino.h>

enum speedFactor {HIGH, LOW};

BLDCController::BLDCController() {
    motor_pins[0] = 5;
    motor_pins[1] = 6;

    pinMode(motor_pins[0], OUTPUT);
    pinMode(motor_pins[1], OUTPUT);
}

void BLDCController::setMotorSpeeds(float left, float right) {
    float multiplier = (speed_factor == HIGH) ? 1.0 : 0.5;

    int pwmLeft = map((int)(left * multiplier * 100), -100, 100, 1000, 2000);
    int pwmRight = map((int)(right * multiplier * 100), -100, 100, 1000, 2000);

    pwmLeft = constrain(pwmLeft, 1000, 2000);
    pwmRight = constrain(pwmRight, 1000, 2000);

    analogWrite(motor_pins[0], map(pwmLeft, 1000, 2000, 0, 255));
    analogWrite(motor_pins[1], map(pwmRight, 1000, 2000, 0, 255));
}

void BLDCController::setSpeedFactor(speedFactor factor) {
    speed_factor = factor;
}