#include "amphibious_drone.h"
#include "Arduino.h"

RC_Receiver receiver;
BLDCController motorController;

void setup() {
    Serial.begin(9600);
}

void loop() {
    drone_control(receiver, motorController);
    // channel_output_test(receiver);
}