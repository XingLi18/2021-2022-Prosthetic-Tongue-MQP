  /* Code for airpump button demo
   *  Air pump turns on for 1 second when button is pressed
  */
  // **** LIBRARIES TO INCLUDE ****
  #include <Wire.h>
  
  // ****** CONSTANTS AND VARIABLES ******
  
  //    PINOUTS - see pinout diagram in Claire's daily updates
  const int 2waySol = 10;     //2 way solenoid to determine whether or not tongue fills up
  const int ledbit = 8; //LED testing pin
  const int btn1 = 2;         // Button 1, D2
  
  //    VARIABLES FOR READINGS
  int frontBtn = 0;     // Button 1 - inflate front
  
  void setup() {
  // solenoids
  pinMode(2waySol, OUTPUT);     // Back Section D10
  
  //LED for testing button
  pinMode(ledbit, OUTPUT);  
  
  //buttons
  pinMode(btn1, INPUT);      // Button 1 D2
  
  // start serial monitor
  Serial.begin(9600);     // print pressure values to serial read out, 9600 baud rate
  }
  
  // ******** MAIN LOOP *******
  void loop() {
    frontBtn = digitalRead(btn1);
  if (frontBtn == HIGH){//button pressed
    digitalWrite(ledbit, HIGH);
    digitalWrite(2waySol, HIGH);
    delay(1000);
    //inflateAll(2); 
  }
  else {//button not pressed
    Serial.println("why no button?");
    digitalWrite(ledbit, LOW);
    digitalWrite(2waySol, LOW);
  }
  Serial.print("Button val = ");
  Serial.println(frontBtn);
  delay(500);
  }


