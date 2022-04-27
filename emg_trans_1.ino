#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10); // CE (yellow), CSN (orange)         
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
//emg will signal output

int firstFiveTime = 0;                //determines if the code has run 5 times to average for threshold

//some default threshold value
float emgThreshold = 2.5;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}

void loop() {
  // read the input on analog pin 0:
  int emgValue = analogRead(A0);
  
 if (emgValue > 0) {//checks to make sure emg sensor is on the person I suppose
  if(firstFiveTime < 5){
    firstFiveTime++;
    emgThreshold = (emgValue + emgThreshold)/2;
    emgThreshold = emgThreshold + 100;
    Serial.println("Threshold update"); 
  
  }
  Serial.print("EMG Threshold ="); 
  Serial.println(emgThreshold);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(emgValue > emgThreshold){//This is where the servo gets turned on and off
   //If emg detects a flex, do this
    const char text[] = "Muscles";
    radio.write(&text, sizeof(text));                  //Sending the message to receiver
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //check emg value
    Serial.print("EMG value = ");
    Serial.println(emgValue);
    Serial.println("Muscle ///////////////////////////////////////////////////////////////////////////////////////////////////////"); 
    
    }
 else {
    const char text[] = "No Muscles";
    radio.write(&text, sizeof(text));                  //Sending the message to receiver 
    Serial.print("EMG value = ");
    Serial.println(emgValue);
    Serial.println("No muscle"); 
    
 }
 
  radio.write(&emgValue, sizeof(emgValue));  //Sending the message to receiver 
  radio.write(&emgThreshold, sizeof(emgThreshold));  //Sending the message to receiver 
  
  delay(100);//will code this out later
}
}


