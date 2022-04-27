//includes
#include <Servo.h> 
#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

//transmitted values
int muscle = 0;

//Timer for servos
unsigned long servTime = 0;  

//"Boolean" for whether or not servo is extended
boolean servOn = 0;                       

const long oneSec   = 1000;           // interval time constants in milliseconds
const long twoSec   = 2000;           
const long fourSec  = 4000;          
const long eightSec = 8000; 

//servos are output
int servoPin1 = 2; // Servo is pin 2

// Create servo 1
Servo Servo1; 

void setup() {
  // put your setup code here, to run once:
  // Servo Setup 
  Servo1.attach(servoPin1); 
   
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}

void loop() {
  unsigned long currTime = millis(); //Timer

 if (radio.available()) {//checks to make sure emg sensor is on the person I suppose
    radio.read(&muscle, sizeof(muscle));    //Reading the data
    //radio.read(&emgValue, sizeof(emgValue));    //Reading the data
    //radio.read(&emgThreshold, sizeof(emgThreshold));    //Reading the data
    
    Serial.print("Muscle on off ");
    Serial.println(muscle);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(muscle){//This is where the servo gets turned on and off
    Serial.println("Muscle on--------------------------------------------------------------------");
   //If resistor detects something, do this
    Serial.print("Current time = ");
    Serial.println(servTime);
   //Every two seconds turn to 180 or 0 degrees
   if((currTime - servTime )>= twoSec){
     servTime = currTime;
     if(servOn){
        Servo1.write(130);//max turn
        servOn = 0;}
     else{
        Servo1.write(0);//Max turn
        servOn = 1;}}
        Serial.println("ENOUGH MUSCLE xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ");
  } 
  else{
    Serial.println("Muscle off ////////////////////////////////////////////////////////////////////////////");
    //If not in use, turn servo off
   if((currTime - servTime )>= twoSec){
     servTime = currTime;
     Servo1.write(0);//max turn
     servOn = 1;}
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      //Some debug code to check if the servo should be moving or not
    if(servOn)
      Serial.println("Servo is moving ");
    else
     Serial.println("Servo is not moving ");

     Serial.println("-------------------- ");
}
 else {
    Serial.println("No radio"); 
    //reset servo
    Servo1.write(0);//default to 0
 }
}


