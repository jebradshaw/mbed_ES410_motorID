# mbed_ES410_motorID
Used to establish motor characteristics for the ES/EW410 course

```C++
#include "mbed.h"
#include "MotCon.h"
#include "QEI.h"
 
#define TSAMPLE     0.010 //******YOU CHANGE how fast you update the control in sec
#define ENC_CPR     800.0
#define PI          3.141592653589793
#define meascount 300      //******YOU CHANGE how many measurements are made 
 
Serial pc(USBTX, USBRX);
DigitalOut led1(LED1);
QEI enc1(p24,p23,NC,800, QEI::X4_ENCODING); //Global Motor 800 cpr w x4 encoding
MotCon motor(p26, p28);       //pwm output, direction
Ticker cont_update;


float enc;
volatile int end_flag = 0;  //must make volatile to share with ticker and while loop
int tcount;
float mot;
//****** following variables are subject to change
float Kspeed;
float sp[meascount];
float motk[meascount];
float tauspec;
float taumotor;
float Dcgain;
float Desspeed;
float e;
float keold;
float ke;
float eold;
float mvold;
float kprop;

void update_controller(void){    
    enc = (float)enc1.getPulses();
    enc1.reset();
    
    sp[tcount]=enc*Kspeed; //calculate the encoder speed
    
    mot=0.3; // *************************YOU CHANGE voltage to detrmine the motr speed
    motor.mot_control(mot);  
    
    tcount++;
    if(tcount == meascount){
        cont_update.detach();   //terminate the Ticker (interrupt routine)
        end_flag = 1;           //indicate that the sampling is over    
    }
    led1 = !led1;
}

int main(){
    pc.printf("Begin ES410 MotorID program\r\n\r\n");
    
    //Initialize variables
    Kspeed=(2.0*PI/ENC_CPR)/(TSAMPLE);
  
                     
    cont_update.attach(&update_controller, TSAMPLE); //start the ticker and controller
    
    while(end_flag == 0); //wait for sample collection to stop
    motor.mot_control(0.0);         //turn off the motor when all of the data is collected    
    
    //serial output
    for(int k=0;k<meascount;k++){ // print the data on the screen so you can download it for processing
        pc.printf("%4d %.2f \n\r",k, sp[k]);        
    }  
}
```
