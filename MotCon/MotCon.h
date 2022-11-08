
#include "mbed.h"

#ifndef MBED_MOTCON_H
#define MBED_MOTCON_H

class MotCon{
public:
      MotCon(PinName _pwm, PinName _dir);
      void mot_control(float dc);
      void mot_control(float dc, int invert);
private:
    PwmOut _pwm;
    DigitalOut _dir;
};

#endif
