#ifndef RC_RECEIVER_H
#define RC_RECEIVER_H

class RC_Receiver {
    public:
        /**
         * @brief Initializes the RC receiver.
         *
         * Assigns the available channels to pins on the arduino uno and sets the pin modes
         * to input.
         */
        RC_Receiver();

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
        
    private:
        static const int NUM_CHANNELS = 6;
        int channel_pins[NUM_CHANNELS];
};

#endif
