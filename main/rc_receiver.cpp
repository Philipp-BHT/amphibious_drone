#include "rc_receiver.h"
#include <Arduino.h>

const ChannelCalibration RCReceiver::JOYSTICK_X = {975, 1959, 1475};
const ChannelCalibration RCReceiver::JOYSTICK_Y = {980, 1955, 1478};

RCReceiver::RCReceiver(bool dev) {
    debug_mode = dev;
    
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

RCReceiver::~RCReceiver() {};

float RCReceiver::normalize_pwm(int pulse_width, const ChannelCalibration& calib) {
    float normalized = (float)(pulse_width - calib.center_raw) /
                       (pulse_width >= calib.center_raw
                           ? (calib.max_raw - calib.center_raw)
                           : (calib.center_raw - calib.min_raw));
    return constrain(normalized, -1.0f, 1.0f);
}

float RCReceiver::read_channel(int channel) {
    if (channel < 1 || channel > NUM_CHANNELS) return 0.0;

    int pin = channel_pins[channel - 1];

    delay(3);
    unsigned long pulse_width = pulseIn(pin, HIGH, 25000);
    float normalized;

    if (channel == 1)
        normalized = normalize_pwm(pulse_width, JOYSTICK_X);
    else if (channel == 2)
        normalized = normalize_pwm(pulse_width, JOYSTICK_Y);
    else
        normalized = ((float)pulse_width - 1500.0f) / 500.0f;

    if (debug_mode && channel == 1) {
        Serial.print("CH");
        Serial.print(channel);
        Serial.print(" raw: ");
        Serial.print(pulse_width);
        Serial.print(" -> norm: ");
        Serial.println(normalized, 3);
    }
    
    return constrain(normalized, -1.0f, 1.0f);
};



int RCReceiver::get_num_channels() {
    return NUM_CHANNELS;
};