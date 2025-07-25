#include <Arduino.h>
#include "drone_controller.h"
#include "rc_receiver.h"
#include "bldc_controller.h"
#include "servo_controller.h"


DroneController::DroneController() {};
DroneController::~DroneController() {};

void DroneController::drone_startup(RC_Receiver& receiver, ServoController& servo, BLDCController& motorController) {
    Serial.print("Drone not armed");
    Serial.println();

    Serial.println("Sending neutral throttle to arm ESCs...");

    delay(3000); 

    Serial.println("Waiting for switches in neutral position...");

    while(1) {
        float ch_5 = receiver.read_channel(5);
        float ch_6 = receiver.read_channel(6);
        ServoDirection ch_6_dir = servo.mapSwitchToDirection(ch_6);
        if (ch_5 > 0.5 && ch_6_dir == STOPPED) {
            motorController.setMotorSpeeds(1500, 1500);
            Serial.print("Drone armed");
            Serial.println();
            armed = true;
            break;
        }
        delay(100);
    }
};

bool DroneController::get_arming_status() {
    return armed;
};


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