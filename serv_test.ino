//servo good stuff
#include <Servo.h> 

// Servo is 2
int servoPin = 2                            ; 

// Create servo1
Servo Servo1; 

void setup() { 
   // Servo Setup 
   Servo1.attach(servoPin); 
}

void loop(){ 
   // serv1 0 degrees 
   Servo1.write(0); 
   delay(2000); 

   
   // serv1 180 degrees
   Servo1.write(180); 
   delay(2000); 

   //loops
}


/*as basic as it gets for the servo, hook red up to 5V or 3.3V (5V has more torque and is faster), 
 to ground, and white to whatever pin you set the servo pin to (in this case 2).  
 It doesnt seem like you can actually change the speed of the servo unless you use a PWM on the red wire i suppose*/ 

