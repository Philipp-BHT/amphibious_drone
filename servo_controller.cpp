#include "servo_controller.h"

ServoController::ServoController(){
    ballast_servo.attach(9);
    servo_state = STOPPED;
};


void ServoController::startBallast(ServoDirection dir) {
    if (dir == FORWARD) ballast_servo.write(180);
    if (dir == REVERSE) ballast_servo.write(0);
    servo_start_time = millis();
    servo_state = dir;
};

void ServoController::updateBallast() {
    if (servo_state != STOPPED && millis() - servo_start_time >= servo_duration) {
        ballast_servo.write(90);
        servo_state = STOPPED;
    };
};