#include "Arduino.h"
#include "drone_controller.h"

DroneController drone;
RC_Receiver receiver;
BLDCController motorController;
ServoController bouyancy_controller;

void setup() {
    Serial.begin(9600);
}

void loop() {
    drone.drone_control(receiver, motorController, bouyancy_controller);
    // drone.channel_output_test(receiver);
}