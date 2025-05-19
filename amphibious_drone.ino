#include "RC_Receiver.h"

RC_Receiver rc;

void setup() {
    Serial.begin(9600);
}

void loop() {
    static int channel = 7;
    float channel_value = 0;

    channel_value = rc.read_channel(channel);
    Serial.print("Channel ");
    Serial.print(channel + 1);
    Serial.print(": ");
    Serial.print(channel_value);
    Serial.println();
    // channel = (channel + 1) % rc.NUM_CHANNELS;

}