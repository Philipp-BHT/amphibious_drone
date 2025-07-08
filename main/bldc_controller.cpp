#include "bldc_controller.h"
#include <Arduino.h>


BLDCController::BLDCController() {};

void BLDCController::begin() {
    escLeft.attach(5);
    escRight.attach(6);
    delay(50);
}


BLDCController::~BLDCController() {};

void BLDCController::setRawPWM(int pwmLeft, int pwmRight) {
    escLeft.writeMicroseconds(pwmLeft);
    escRight.writeMicroseconds(pwmRight);
}

void BLDCController::setMotorSpeeds(float channel_1, float channel_2) {
    float multiplier = (speed_factor == SPEED_HIGH) ? 0.25 : 0.1;

    float mL = fmax(-1.0, fmin(1.0, channel_2 + channel_1));
    float mR = fmax(-1.0, fmin(1.0, channel_2 - channel_1));

    if (fabs(mL) < 0.1) mL = 0.0;
    if (fabs(mR) < 0.1) mR = 0.0;

    if (mL == 0 && mR == 0) {
        escLeft.writeMicroseconds(1490);
        escRight.writeMicroseconds(1490);
        return;
    }

    mL *= multiplier;
    mR *= multiplier;

    const int PWM_LEFT_MIN = 974;
    const int PWM_LEFT_MAX = 1964;
    const int PWM_RIGHT_MIN = 966;
    const int PWM_RIGHT_MAX = 1965;

    int dutyLeft = map((int)(mL * 100), -100, 100, PWM_LEFT_MIN, PWM_LEFT_MAX);
    int dutyRight = map((int)(mR * 100), -100, 100, PWM_RIGHT_MIN, PWM_RIGHT_MAX);

    dutyLeft = constrain(dutyLeft, PWM_LEFT_MIN, PWM_LEFT_MAX);
    dutyRight = constrain(dutyRight, PWM_RIGHT_MIN, PWM_RIGHT_MAX);

    Serial.print("dutyLeft: ");
    Serial.print(dutyLeft);
    Serial.print("    dutyRight: ");
    Serial.println(dutyRight);

    escLeft.writeMicroseconds(dutyLeft);
    escRight.writeMicroseconds(dutyRight);
}

void BLDCController::setSpeedFactor(speedFactor factor) {
    if (factor != speed_factor) {
        speed_factor = factor;
        Serial.print("Changed speed factor to: ");
        Serial.println(speed_factor == SPEED_HIGH ? "HIGH" : "LOW");
        Serial.println();
    }
}