#include <Servo.h> 

//Control Module Code from '20-'21 modified to use a servo instead of solenoid
int fsrPin = A0; //Force Sensor Variables
int fsrReading;
int fsrVoltage;
unsigned long fsrResistance; //Voltage converted to resistance value which can be long.
unsigned long fsrResistanceT = 40000; //Resistance threshold
unsigned long fsrConductance;
long fsrForce; //Convert resistance to force
///int electromagnet = 13; //Electromagnet is connected to digital pin 3
#define control 8  //I guess 8 is the digital pin 3?

//seperate timers for solenoids and servos
unsigned long servTime = 0;        
unsigned long solTime  = 0;        

//Checks whether servo or solenoid is on or off
int servOn = 0;
int solOn  = 0;

const long oneSec   = 1000;           // interval constants in milliseconds
const long twoSec   = 2000;           
const long fiveSec  = 5000;          
const long eightSec = 8000; 

         //determines if the code has run 5 times to average for threshold
    int firstFiveTime = 0;
// Servo is 2
int servoPin = 2; 
int servoPin2 = 3; 

// Create servos
Servo Servo1; 
Servo Servo2; 

void setup() {
// put your setup code here, to run once:
// Servo Setup 
   Servo1.attach(servoPin); 
   Servo2.attach(servoPin2);

Serial.begin(9600);
pinMode(control, OUTPUT); //Make pin 3 the output
}

void loop() {
  //Same current time for both
  unsigned long currTime = millis();

 // put your main code here, to run repeatedly:
 fsrReading = analogRead(fsrPin); 
 Serial.print("Analog reading = ");
 Serial.println(fsrReading);
 
 // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
 fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
 Serial.print("Voltage reading in mV = ");
 Serial.println(fsrVoltage); 
 
 if (fsrVoltage > 0) {
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= fsrVoltage;

 if(firstFiveTime < 5){
  firstFiveTime++;
  fsrResistanceT = (fsrResistanceT + fsrResistance)/2;
  fsrResistanceT = fsrResistanceT + 250;
  Serial.println("Threshold update"); 
}
   Serial.print("Threshold Resistance = ");
  Serial.println(fsrResistanceT); 
   //Every two seconds turn mosfet off or on
   /*if(currTime - solTime >= oneSec){
     solTime = currTime;
     if(solOn){
        digitalWrite(control,HIGH); // turn the MOSFET Switch ON
        solOn = 0;}
     else{
        digitalWrite(control,LOW); // turn the MOSFET Switch OFF
        solOn = 1;}}*/

  if(fsrResistance > fsrResistanceT){//set threshold here
   //If resistor detects something, do this
    Serial.print("Current time = ");
    Serial.println(servTime);
   //Every two seconds turn to 180 or 0 degrees
   if((currTime - servTime )>= twoSec){
     servTime = currTime;
     if(servOn){
        Servo1.write(180);//max turn
        Servo2.write(180);//max turn
        digitalWrite(control,HIGH); // turn the MOSFET Switch ON
        servOn = 0;}
        
     else{
        Servo1.write(0);
        Servo2.write(0);//max turn
        digitalWrite(control,LOW); // turn the MOSFET Switch OFF
        servOn = 1;}
        }
        Serial.println("ENOUGH PRESSURE xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ");
  } 
  else{
    //If not in use, turn servo off
   if((currTime - servTime )>= twoSec){
     servTime = currTime;
     Servo1.write(0);//max turn
     Servo2.write(0);//max turn
     digitalWrite(control,LOW); // turn the MOSFET Switch OFF
     servOn = 1;}
  }

    Serial.print("FSR resistance in ohms = ");
    Serial.println(fsrResistance);
    fsrConductance = 1000000;         
    fsrConductance /= fsrResistance;
    Serial.print("Conductance in microMhos: ");
    Serial.println(fsrConductance);
   
   if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);     
        
   } else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);           
   }

    //checking if servOn and solOn work
    if(servOn)
      Serial.println("Servo is moving ");
    else
     Serial.println("Servo is not moving ");
    if(solOn)
      Serial.println("Solenoid is powered ");  
    else
     Serial.println("Solenoid is not moving ");
 Serial.println("-------------------- ");
}

 else {
    Serial.println("No pressure"); 
    delay(250);
    //reset servo
    Servo1.write(0);
    Servo2.write(0);//max turn
    digitalWrite(control,LOW); // Turn the MOSFET Switch OFF
 }
}

//Link to GitHub 
//https://github.com/XingLi18/2021-2022-Prosthetic-Tongue-MQP/blob/main/20-21%20Control%20Module%20Arduino%20Code 

