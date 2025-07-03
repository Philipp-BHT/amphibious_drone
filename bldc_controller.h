#ifndef BLDC_CONTROLLER_H
#define BLDC_CONTROLLER_H

/**
 * @brief Speed factor used to scale motor output.
 *
 * HIGH applies a higher speed multiplier, LOW applies a reduced one.
 */
enum speedFactor {HIGH, LOW};

class BLDCController {
public:
    /**
     * @brief Initializes motor pins and sets pin modes to OUTPUT.
     */
    BLDCController();
    
    ~BLDCController();

    /**
     * @brief Sets motor speeds based on joystick channel input.
     *
     * Combines left/right (channel 1) and forward/backward (channel 2)
     * input to calculate motor speeds, applies speed scaling,
     * and sends PWM signals to the motor pins.
     *
     * @param channel_1 Left/right joystick input (range -1 to 1)
     * @param channel_2 Forward/backward joystick input (range -1 to 1)
     */
    void setMotorSpeeds(float channel_1, float channel_2);

    /**
     * @brief Sets the speed factor mode (HIGH or LOW).
     *
     * @param factor Speed mode to apply
     */
    void setSpeedFactor(speedFactor factor);

private:
    int motor_pins[2];                  ///< PWM output pins for left and right motors
    speedFactor speed_factor = LOW;     ///< Current speed mode
};

#endif