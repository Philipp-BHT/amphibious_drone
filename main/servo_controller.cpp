#include <Arduino.h>
#include "servo_controller.h"


ServoController::ServoController(){
    ballast_servo.attach(2);
    servo_state = STOPPED;
    ballast_servo.write(87);
};

ServoController::~ServoController() {};

void ServoController::begin() {
    ballast_servo.attach(2);
    delay(50);
    servo_state = STOPPED;
    ballast_servo.write(87);
}

void ServoController::startBallast(ServoDirection dir) {
    if (dir != servo_state) {
        Serial.print("Changing ballast direction to: ");
        Serial.println(dir);
        
        if (dir == STOPPED) ballast_servo.write(87);
        if (dir == FORWARD) ballast_servo.write(180);
        if (dir == REVERSE) ballast_servo.write(0);

        servo_start_time = millis();
        servo_state = dir;
    }
};

void ServoController::updateBallast() {
    if (servo_state != STOPPED && millis() - servo_start_time >= servo_duration) {
        ballast_servo.write(87);
        servo_state = STOPPED;
    };
};

void ServoController::setBallast(int val) {
    ballast_servo.write(val);
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