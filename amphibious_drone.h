#ifndef AMPHIBIOUS_DRONE_H
#define AMPHIBIOUS_DRONE_H

#include "RC_Receiver.h"
#include "bldc_controller.h"
#include "servo_controller.h"

class DroneController {
    private:
    DroneController();
    ~DroneController();

    public:
    void drone_control(RC_Receiver& receiver, BLDCController& motorController, ServoController& bouyancy_controller);
    void channel_output_test(RC_Receiver& receiver);
}


#endif