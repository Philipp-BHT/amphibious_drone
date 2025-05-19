#ifndef RC_RECEIVER_H
#define RC_RECEIVER_H

class RC_Receiver {
    public:
        RC_Receiver();
        ~RC_Receiver();
        float read_channel(int channel);
        static const int NUM_CHANNELS = 6;
        
    private:
        int channel_pins[NUM_CHANNELS];
};

#endif
