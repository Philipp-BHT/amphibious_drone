#ifndef AMPHIBIOUS_DRONE_H
#define AMPHIBIOUS_DRONE_H

#include "RC_Receiver.h"
#include "bldc_controller.h"

void drone_control(RC_Receiver& receiver, BLDCController& motorController);
void channel_output_test(RC_Receiver& receiver);

#endif