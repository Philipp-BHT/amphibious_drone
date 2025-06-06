#ifndef BLDC_CONTROLLER_H
#define BLDC_CONTROLLER_H

enum speedFactor {HIGH, LOW};

class BLDCController {
public:
    BLDCController();
    void setMotorSpeeds(float left, float right);
    void setSpeedFactor(speedFactor factor);

private:
    int motor_pins[2];
    speedFactor speed_factor = LOW;
};

#endif