#include "MotCon.h"

//Constructor
MotCon::MotCon(PinName pwm, PinName dir) : _pwm(pwm), _dir(dir) {
    _pwm.period_us(50);
    _pwm = 0.0;
    _dir = 0;
}

// dc is signed duty cycle (+/-1.0)
void MotCon::mot_control(float dc){        
    if(dc>1.0)
        dc=1.0;
    if(dc<-1.0)
        dc=-1.0;
        
    if(dc > 0.001){
        _dir = 0;
        _pwm = dc;
    }
    else if(dc < -0.001){
        _dir = 1;
        _pwm = abs(dc);
    }
    else{
        _dir = 0;
        _pwm = 0.0;
    }      
}

// dc is signed duty cycle (+/-1.0)
void MotCon::mot_control(float dc, int invert){        
    if(dc>1.0)
        dc=1.0;
    if(dc<-1.0)
        dc=-1.0;
        
    if(invert==0){
        if(dc > 0.001){
            _dir = 0;
            _pwm = dc;
        }
        else if(dc < -0.001){
            _dir = 1;
            _pwm = abs(dc);
        }
        else{
            _dir = 0;
            _pwm = 0.0;
        }
    }
    else{
        if(dc > 0.001){
            _dir = 1;
            _pwm = dc;
        }
        else if(dc < -0.001){
            _dir = 0;
            _pwm = abs(dc);
        }
        else{
            _dir = 0;
            _pwm = 0.0;
        }
    }
}
