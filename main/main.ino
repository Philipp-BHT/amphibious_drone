#include "Arduino.h"
#include "drone_controller.h"

DroneController drone;
RCReceiver receiver(false);
BLDCController *motorController;
ServoController* bouyancy_controller;

void setup() {
    Serial.begin(9600);
    delay(50);
    bouyancy_controller = new ServoController();
    bouyancy_controller->begin();        

    motorController = new BLDCController();
    motorController->begin();
}

void loop() {
    if (!drone.get_arming_status()) {
        drone.drone_startup(receiver, *bouyancy_controller, *motorController);  
    } else {
        drone.drone_control(receiver, *motorController, *bouyancy_controller);
    }
}