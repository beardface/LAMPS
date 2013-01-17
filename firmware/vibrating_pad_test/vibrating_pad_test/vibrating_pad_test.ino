/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(32, OUTPUT);   //OK
  pinMode(34, OUTPUT);   //BAD
  pinMode(36, OUTPUT);   //BAD
  pinMode(38, OUTPUT);   // 
}

void loop() {
  digitalWrite(34, HIGH);   // set the LED on
  digitalWrite(36, HIGH);   // set the LED on
  delay(500);              // wait for a second
  digitalWrite(34, LOW);    // set the LED offnd
  digitalWrite(36, LOW);    // set the LED off
  delay(500);              // wait for a second
  digitalWrite(34, HIGH);   // set the LED on
  digitalWrite(36, HIGH);   // set the LED on
  delay(500);              // wait for a second
  digitalWrite(34, LOW);    // set the LED offnd
  digitalWrite(36, LOW);    // set the LED off
  delay(500);              // wait for a second
  digitalWrite(34, HIGH);   // set the LED on
  digitalWrite(36, HIGH);   // set the LED on
  delay(500);              // wait for a second
  digitalWrite(34, LOW);    // set the LED offnd
  digitalWrite(36, LOW);    // set the LED off
  delay(100);              // wait for a second
  delay(5000);              // wait for a second
}
