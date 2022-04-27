int fsrPin = A0; //Force Sensor Variables
int fsrReading;
unsigned long fsrT = 200; //Resistance threshold
#define control 8  //I guess 8 is the digital pin 3?

//solenoid timer
unsigned long solTime  = 0;        

//Checks whether solenoid is on or off
int solOn  = 0;

const long oneSec   = 1000;           // interval constants in milliseconds
const long twoSec   = 2000;           
const long fourSec  = 4000;          
const long eightSec = 8000; 

int firstFiveTime = 0; //determines if the code has run 5 times to average for threshold 

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
pinMode(control, OUTPUT); //Make pin 8 (solenoid) the output
}

void loop() { // put your main code here, to run repeatedly:
  //Same current time for both
  unsigned long currTime = millis();

 fsrReading = analogRead(fsrPin); //read pressure sensor
 Serial.print("Analog reading = ");
 Serial.println(fsrReading);
 
 if (fsrReading > 0) {//if its reads pressure sensor

 if(firstFiveTime < 5){
  firstFiveTime++;
  fsrT = (fsrT + fsrReading)/2;
  fsrT = fsrT + 5;//edits sensitivity of threshold value
  Serial.println("Threshold update"); 
}
   Serial.print("Threshold Resistance = ");
  Serial.println(fsrT); 

  if(fsrReading > fsrT){//set threshold here
   //If resistor detects something, do this
    Serial.print("Current time = ");
    Serial.println(currTime );
    Serial.print("Solenoid timer = ");
    Serial.println(solTime );

   //Every two seconds turn mosfet off or on
   if(currTime - solTime >= oneSec){
     solTime = currTime;
     if(solOn){
        digitalWrite(control,HIGH); // turn the MOSFET Switch ON
        solOn = 0;
         Serial.println("ENOUGH PRESSURE xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ");}
     else{
        digitalWrite(control,LOW); // turn the MOSFET Switch OFF
        solOn = 1;
        Serial.println("ENOUGH PRESSURE oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
  } 
   }
   Serial.println("Solenoid is not powered");
  }
  
  else{
    //If not in use, turn solenoid off
     solTime = currTime;
     digitalWrite(control,LOW); // turn the MOSFET Switch OFF
     Serial.println("Solenoid is not powered");
     solOn = 1;
  }  

 Serial.println("-------------------- ");
}

 else {//if it does not read pressure sensor
    Serial.println("No pressure"); 
    delay(250);
    digitalWrite(control,LOW); // Turn the MOSFET Switch OFF
 }
}


