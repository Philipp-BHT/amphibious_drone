#include <Arduino.h>
#include "drone_controller.h"
#include "rc_receiver.h"
#include "bldc_controller.h"
#include "servo_controller.h"


DroneController::DroneController() {};
DroneController::~DroneController() {};


void DroneController::drone_control(RC_Receiver& receiver, BLDCController& motorController, ServoController& bouyancyController) {
    float joystick_x = receiver.read_channel(1);
    float joystick_y = receiver.read_channel(2);
    float speed_mode_switch = receiver.read_channel(5);
    float buoyancy_control = receiver.read_channel(6);

    motorController.setSpeedFactor(speed_mode_switch > 0 ? HIGH : LOW);
    motorController.setMotorSpeeds(joystick_x, joystick_y);

    ServoDirection dir = bouyancyController.mapSwitchToDirection(buoyancy_control);
    bouyancyController.startBallast(dir);
}


void DroneController::channel_output_test (RC_Receiver& receiver, int channel = 1, bool cycle_channels = false) {
    float channel_value = 0;

    channel_value = receiver.read_channel(channel);
    Serial.print("Channel ");
    Serial.print(channel + 1);
    Serial.print(": ");
    Serial.print(channel_value);
    Serial.println();
    if (cycle_channels)
        channel = (channel + 1) % receiver.get_num_channels();
}