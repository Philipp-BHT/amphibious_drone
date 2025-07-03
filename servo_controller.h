#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Servo.h>

enum ServoDirection { STOPPED, FORWARD, REVERSE };

class ServoController {
    public:
        ServoController();
        ~ServoController();
        void startBallast(ServoDirection dir);
        void updateBallast();
        ServoDirection ServoController::mapSwitchToDirection(float input);

    private:
        ServoDirection servo_state;
        Servo ballast_servo;
        unsigned long servo_start_time;
        unsigned long servo_duration;
        
};

#endif