//includes
#include <Servo.h> 
#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

//1 for enough muscle, 0 for no muscle
boolean muscle_state = 0;

//Timer for servos
unsigned long servTime = 0;  

//"Boolean" for whether or not servo is extended
boolean servOn = 0;                       

const long oneSec   = 1000;           // interval time constants in milliseconds
const long twoSec   = 2000;           
const long fourSec  = 4000;          
const long eightSec = 8000; 

//servos are output
int servoPin1 = 2; // Servo is pin 2 and 3
int servoPin2 = 3; 

// Create servo 1 and 2
Servo Servo1; 
Servo Servo2; 

void setup() {
  // put your setup code here, to run once:
  // Servo Setup 
  Servo1.attach(servoPin1); 
  Servo2.attach(servoPin2); 
   
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}

void loop() {
  unsigned long currTime = millis(); //Timer
  int emgValue;
  float emgThreshold;

 if (radio.available()) {//checks to make sure emg sensor is on the person I suppose
    char text[32] = "";                 //Saving the incoming data
    radio.read(&text, sizeof(text));    //Reading the data
    radio.read(&emgValue, sizeof(emgValue));    //Reading the data
    radio.read(&emgThreshold, sizeof(emgThreshold));    //Reading the data

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(emgValue > emgThreshold){//This is where the servo gets turned on and off
   //If resistor detects something, do this
    Serial.print("Current time = ");
    Serial.println(servTime);
   //Every two seconds turn to 180 or 0 degrees
   if((currTime - servTime )>= twoSec){
     servTime = currTime;
     if(servOn){
        Servo1.write(180);//max turn
        Servo2.write(180);//max turn
        servOn = 0;}
     else{
        Servo1.write(0);
        Servo2.write(0);//max turn
        servOn = 1;}}
        Serial.println("ENOUGH MUSCLE xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ");
  } 
  else{
    //If not in use, turn servo off
   if((currTime - servTime )>= twoSec){
     servTime = currTime;
     Servo1.write(0);//max turn
     Servo2.write(0);//max turn
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
    delay(250);
    //reset servo
    Servo1.write(0);
    Servo2.write(0);//max turn
 }
}


