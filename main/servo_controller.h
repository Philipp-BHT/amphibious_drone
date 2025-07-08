#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Servo.h>

enum ServoDirection { STOPPED, REVERSE, FORWARD};

class ServoController {
    public:

        /**
         * @brief Initializes the Servo motor controller.
         *
         * Attaches the servo motor to the designated pin and sets its initial state to STOPPED.
         */
        ServoController();
        ~ServoController();

        void begin(); 

        /**
         * @brief Starts the rotation of the ballast tank servo motor.
         *
         * Writes a command to the servo to rotate in the specified direction (FORWARD or REVERSE),
         * records the start time, and updates the servo state.
         *
         * @param dir Rotational direction (FORWARD or REVERSE)
         */
        void startBallast(ServoDirection dir);

        /** 
         * @brief Stops the ballast motor if the rotation time exceeds the allowed duration.
         *
         * Checks whether the servo is currently rotating. If so, it compares the elapsed time
         * since activation to the predefined rotation duration. If the duration is exceeded,
         * the servo is stopped (by sending a 90 deg command) and the state is set to STOPPED.
         */
        void updateBallast();

        void setBallast(int val);

        /** 
         * @brief Maps a float value to an enum representing rotational direction.
         *
         * If the input value is > 0.5 the value is interpreted as forward rotation, a value 
         * of < -0.5 is interpreted as reverse rotation. A value in between is interpreted as 
         * no rotation.  
         */
        ServoDirection ServoController::mapSwitchToDirection(float input);

    private:
        ServoDirection servo_state;
        Servo ballast_servo;
        unsigned long servo_start_time;
        unsigned long servo_duration;
        
};

#endif