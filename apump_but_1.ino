//https://github.com/casellen/ArtificialTongue19-20

/* Test Bench code for Artificial Tongue - V1a
 *  Basic timed inflation code to test seal on tongue/misc things
 *  Loop reads pressure sensor 1 and prints value to LCD
 */
// **** LIBRARIES TO INCLUDE ****
#include <Wire.h>

// ****** CONSTANTS AND VARIABLES ******

//    PINOUTS - see pinout diagram in Claire's daily updates
const int backSol = 10;     //Back Section D10
const int btn1 = 2;         // Button 1, D2
const int pres_1 = A3;       // pressure sensor 1 (white wire), A3

// OTHER MISC CONSTANTS
int Pmin = 0;   // minimum pressure reading on sensor
//    VARIABLES FOR READINGS
int frontBtn = 0;     // Button 1 - inflate front
float cur_pres;     // initialize cur_pres array to store pressure values

void setup() {
  // solenoids
  pinMode(backSol, OUTPUT);     // Back Section D10
  
  //buttons
  pinMode(btn1, INPUT);      // Button 1 D2

  // set up pressure sensors
  pinMode(pres_1, INPUT);     // Pressure sensor 1

  // start serial monitor
   Serial.begin(9600);     // print pressure values to serial read out, 9600 baud rate
}
// ****** HELPER FUNCTIONS ******

void inflateSection(int section, int sec) {
  /*
   * Takes in section and time, inflates for that long
   */
   digitalWrite(section, HIGH);     // section on
   delay(sec*1000);                  // run for time
   digitalWrite(section, LOW);      // turn off
}

void inflateAll(int sec) {
  /*
   * takes in time and Pin Val, inflates all sections for that long, then turns off solenoids
   */
   
   digitalWrite(backSol, HIGH);
   delay(sec*1000);
   cur_pres = readPressure(pres_1);    // Read out pressure sensor WHILE inflating! - Sensor 1
   delay(250);
   digitalWrite(backSol, LOW);
}

float readPressure(int pin) {
  /*
   * takes in pressure sensor pin, 
   * returns output pressure 
   * modified from soft robotics toolkit
   */
   int sensorValue = analogRead(pin);       // reads sensor value
   
   // convert sensor value to voltage
   float voltage = (float)sensorValue * (5.0f / 1023.0f);

   // convert volts to PSI
   float pressure_Value = ((voltage - (0.10f * 5.0f)) / (0.80f * 5.0f)) * 30.0f;
   
   // return PSI value
   return pressure_Value;
   }

// ******** MAIN LOOP *******
void loop() {
  inflateAll(2);
  Serial.println(cur_pres[0]);
  delay(500);
}

