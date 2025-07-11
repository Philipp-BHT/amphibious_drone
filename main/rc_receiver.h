#ifndef RC_RECEIVER_H
#define RC_RECEIVER_H

struct ChannelCalibration {
    int min_raw;     
    int max_raw;     
    int center_raw;  
};

class RC_Receiver {
    public:
        /**
         * @brief Initializes the RC receiver.
         *
         * Assigns the available channels to pins on the arduino uno and sets the pin modes
         * to input.
         * 
         * @param dev Boolean that determines if debug messages should be printed.
         */
        RC_Receiver(bool dev = false); 

        ~RC_Receiver();

        /**
         * @brief Reads a channel value from a PWM signal and returns it as a normalized float.
         *
         * The function checks if the selected channels is among the valid channels, and if so,
         * determines the pulse width of the signal on that pin bound to that channel . 
         * That pulse width is normalized, clamped to values between [-1, 1] and returned as a float.
         * 
         * @param channel Channel to be read.
         */
        float read_channel(int channel);
        int get_num_channels();

        float normalize_pwm(int pulse_width, const ChannelCalibration& calib);

        static const ChannelCalibration JOYSTICK_X;
        static const ChannelCalibration JOYSTICK_Y;
        
    private:
        static const int NUM_CHANNELS = 6;
        int channel_pins[NUM_CHANNELS];
        bool debug_mode;
};

#endif
