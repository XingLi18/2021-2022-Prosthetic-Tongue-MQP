  /* Code for airpump button demo
   *  Air pump turns on for 1 second when button is pressed
   * Doesnt include code for test LED
  */
  // **** LIBRARIES TO INCLUDE ****
  #include <Wire.h>
  
  // ****** CONSTANTS AND VARIABLES ******
  
  //    PINOUTS - see pinout diagram in Claire's daily updates
  const int TwoWaySol = 10;     //2 way solenoid to determine whether or not tongue fills up
  const int btn1 = 2;         // Button 1, D2
  
  //    VARIABLES FOR READINGS
  int BtnVal = 0;     // Button 1 - inflate front
  
  void setup() {
  // solenoids
  pinMode(TwoWaySol, OUTPUT);     // 2 way solenoid setup
  
  //buttons
  pinMode(btn1, INPUT);      // Button 1
  
  // start serial monitor
  Serial.begin(9600);     // print pressure values to serial read out, 9600 baud rate
  }
  
  // ******** MAIN LOOP *******
  void loop() {
    BtnVal = digitalRead(btn1);
  if (BtnVal == HIGH){//button pressed
    digitalWrite(TwoWaySol, HIGH);
    delay(1000);
    //inflateAll(2); 
  }
  else {//button not pressed
    Serial.println("why no button?");
    digitalWrite(TwoWaySol, LOW);
  }
  Serial.print("Button val = ");
  Serial.println(BtnVal);
  delay(500);
  }

