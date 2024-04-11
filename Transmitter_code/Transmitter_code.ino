/*
6 channel nrf24l01 transmitter and receiver code.
 */

#include <SPI.h>  // library used for 
#include <RF24.h>  // library used for transmission of data using Nrf module 
#include <nRF24L01.h>

// declaring where the toggle switches are connected in Arduino
int toggleSwitch01pin = 2;

// declaring where the leftHandside joystick is connected
int joystickLeft_VRxPin = A0;
int joystickLeft_VRyPin = A1;

// declaring where the rightHandside joystick is connected
int joystickRight_VRxPin = A2;
int joystickRight_VRyPin = A3;

RF24 radio(7,8);
const byte address[] = "node1";

void setup() {
  Serial.begin(9600); // Initialize Serial communication with a baud rate of 9600
  while (!Serial);    // Wait for Serial Monitor to open
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();  
  pinMode(toggleSwitch01pin, INPUT);
}


struct datapack{
  bool toggleSwitch01 ; 
  
  int joystickLeft_x ;
  int joystickLeft_y ;

  int joystickRight_x ;
  int joystickRight_y ;  
};
datapack data;
void loop() {
  data.toggleSwitch01 = digitalRead(toggleSwitch01pin);

  data.joystickLeft_x = map(analogRead(joystickLeft_VRxPin), 0, 1023,0,255);
  data.joystickLeft_y = map(analogRead(joystickLeft_VRyPin), 0, 1023,0,255);

  data.joystickRight_x = map(analogRead(joystickRight_VRxPin), 0, 1023,0,255); 
  data.joystickRight_y = map(analogRead(joystickRight_VRyPin), 0, 1023,0,255);
  
  // Print the values to the Serial Monitor
  Serial.print("Toggle Switch: ");
  Serial.println(data.toggleSwitch01);
  

  Serial.print("Joystick Left X: ");
  Serial.println(data.joystickLeft_x);

  Serial.print("Joystick Left Y: ");
  Serial.println(data.joystickLeft_y);

  Serial.print("Joystick Right X: ");
  Serial.println(data.joystickRight_x);

  Serial.print("Joystick Right Y: ");
  Serial.println(data.joystickRight_y);



  Serial.println(); // Print a blank line for readability

  delay(5000);
  
  radio.write(&data, sizeof(data)); // Send the data over NRF24L01
}