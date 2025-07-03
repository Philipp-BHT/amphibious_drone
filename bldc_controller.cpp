#include "bldc_controller.h"
#include <Arduino.h>

/**
 * @brief Speed factor used to scale motor output.
 *
 * HIGH applies a larger multiplier to motor speed; LOW applies a smaller one.
 */
enum speedFactor {HIGH, LOW};

/**
 * @brief Initializes the BLDC motor controller.
 *
 * Sets motor pin numbers and configures them as output.
 */
BLDCController::BLDCController() {
    motor_pins[0] = 5;
    motor_pins[1] = 6;

    pinMode(motor_pins[0], OUTPUT);
    pinMode(motor_pins[1], OUTPUT);
}

BLDCController::~BLDCController() {};

/**
 * @brief Sets the motor speeds based on joystick inputs from channel 1 and channel 2.
 *
 * This function takes the normalized joystick input values (range [-1, 1])
 * and calculates the speed for each motor using the drive formula:
 *   - Left motor:  channel_2 + channel_1
 *   - Right motor: channel_2 - channel_1
 *
 * The resulting values are clamped to the range [-1, 1], scaled by a speed multiplier
 * (depending on the current speed mode), and mapped to PWM duty cycle values (0–255)
 * which are written to the motor pins using analogWrite.
 *
 * @param channel_1 Joystick left/right input (RC channel 1)
 * @param channel_2 Joystick forward/backward input (RC channel 2)
 */
void BLDCController::setMotorSpeeds(float channel_1, float channel_2) {
    float multiplier = (speed_factor == HIGH) ? 0.25 : 0.1;

    float mL = fmax(-1.0, fmin(1.0, channel_2 + channel_1));
    float mR = fmax(-1.0, fmin(1.0, channel_2 - channel_1));

    mL *= multiplier;
    mR *= multiplier;

    int pwmLeft = map((int)(mL * 100), -100, 100, 0, 255); 
    int pwmRight = map((int)(mR * 100), -100, 100, 0, 255);

    analogWrite(motor_pins[0], pwmLeft);
    analogWrite(motor_pins[1], pwmRight);
}

/**
 * @brief Sets the current speed mode.
 *
 * Updates the internal speed factor used to scale motor output.
 *
 * @param factor Speed mode to apply (e.g., LOW or HIGH).
 */
void BLDCController::setSpeedFactor(speedFactor factor) {
    speed_factor = factor;
}