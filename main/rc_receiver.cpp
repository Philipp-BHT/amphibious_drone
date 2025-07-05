#include "rc_receiver.h"
#include <Arduino.h>


RC_Receiver::RC_Receiver() {
    channel_pins[0] = 3; 
    channel_pins[1] = 4; 
    channel_pins[2] = 7; 
    channel_pins[3] = 8; 
    channel_pins[4] = 12; 
    channel_pins[5] = 13; 

    for (int i = 0; i < NUM_CHANNELS; i++) {
        pinMode(channel_pins[i], INPUT);
    }

};

RC_Receiver::~RC_Receiver() {};

float RC_Receiver::read_channel(int channel) {
    if (channel < 1 || channel > NUM_CHANNELS) return 0.0;

    int pin = channel_pins[channel - 1];

    delay(3);
    unsigned long pulse_width = pulseIn(pin, HIGH, 25000);

    float normalized = ((float)pulse_width - 1500.0f) / 500.0f;
    return constrain(normalized, -1.0f, 1.0f);
};


int RC_Receiver::get_num_channels() {
    return NUM_CHANNELS;
};