#include "servo_controller.h"


/**
 * @brief Initializes the Servo motor controller.
 *
 * Attaches the servo motor to the designated pin and sets its initial state to STOPPED.
 */
ServoController::ServoController(){
    ballast_servo.attach(9);
    servo_state = STOPPED;
};

/**
 * @brief Destructor for the ServoController class.
 *
 * Currently does nothing, but included for completeness or future cleanup.
 */
ServoController::~ServoController() {};

/**
 * @brief Starts the rotation of the ballast tank servo motor.
 *
 * Writes a command to the servo to rotate in the specified direction (FORWARD or REVERSE),
 * records the start time, and updates the servo state.
 *
 * @param dir Rotational direction (FORWARD or REVERSE)
 */
void ServoController::startBallast(ServoDirection dir) {
    if (dir == FORWARD) ballast_servo.write(180);
    if (dir == REVERSE) ballast_servo.write(0);
    servo_start_time = millis();
    servo_state = dir;
};


/**
 * @brief Stops the ballast motor if the rotation time exceeds the allowed duration.
 *
 * Checks whether the servo is currently rotating. If so, it compares the elapsed time
 * since activation to the predefined rotation duration. If the duration is exceeded,
 * the servo is stopped (by sending a 90° command) and the state is set to STOPPED.
 */
void ServoController::updateBallast() {
    if (servo_state != STOPPED && millis() - servo_start_time >= servo_duration) {
        ballast_servo.write(90);
        servo_state = STOPPED;
    };
};


ServoDirection ServoController::mapSwitchToDirection(float input) {
    if (input > 0.5f) {
        return FORWARD;
    } else if (input < -0.5f) {
        return REVERSE;
    } else {
        return STOPPED;
    }
}