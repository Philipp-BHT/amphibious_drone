#ifndef DRONE_CONTROLLER_H
#define DRONE_CONTROLLER_H

#include "rc_receiver.h"
#include "bldc_controller.h"
#include "servo_controller.h"

class DroneController {
    private:
        bool armed = false;

    public:
    DroneController();
    ~DroneController();

    
    /**
     * @brief Reads RC channel values and controls motor and ballast systems accordingly.
     *
     * This function reads values from RC channels 1, 2, 5, and 6. Channel 5 is used to set
     * the motor speed mode (LOW or HIGH). Channels 1 and 2 are used to control motor direction
     * and speed. Channel 6 controls the direction of the servo responsible for the ballast 
     * tank by mapping it to a ServoDirection value.
     * 
     * @param receiver Reference to an RC_Receiver instance.
     * @param motorController Reference to a BLDCController instance.
     * @param buoyancyController Reference to a ServoController instance.
     */
    void drone_control(RC_Receiver& receiver, BLDCController& motorController, ServoController& bouyancy_controller);

    /**
     * @brief Reads RC channel 5 and 6 and waits until they are in startup position.
     *
     * On startup, waits until channel 5 and 6 are in startup position. Once they are in startup 
     * position, breaks  the loop and returns 1 in order to commence regular operation 
     * 
     * @param receiver Reference to an RC_Receiver instance.
     */
    void drone_startup(RC_Receiver& receiver, ServoController& servo, BLDCController& motorController);

    bool get_arming_status();

    /**
     * @brief Reads channel values and prints the output.
     *
     * Reads the value of the specified 
     * 
     * @param receiver Reference to an RC_Receiver instance.
     * @param motorController Reference to a BLDCController instance.
     * @param buoyancyController Reference to a ServoController instance.
     */
    void channel_output_test(RC_Receiver& receiver, int channel, bool cycle_channels);
};


#endif