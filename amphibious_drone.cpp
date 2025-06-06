#include "amphibious_drone.h"
#include "RC_Receiver.h"
#include "bldc_controller.h"


void drone_control(RC_Receiver& receiver, BLDCController& motorController) {
    float left_input = receiver.read_channel(1);
    float right_input = receiver.read_channel(2);
    float switch_value = receiver.read_channel(3);

    motorController.setSpeedFactor(switch_value > 0 ? HIGH : LOW);
    motorController.setMotorSpeeds(left_input, right_input);
}


void channel_output_test (RC_Receiver& receiver) {
    static int channel = 7;
    float channel_value = 0;

    channel_value = receiver.read_channel(channel);
    Serial.print("Channel ");
    Serial.print(channel + 1);
    Serial.print(": ");
    Serial.print(channel_value);
    Serial.println();
    // channel = (channel + 1) % rc.NUM_CHANNELS;
}