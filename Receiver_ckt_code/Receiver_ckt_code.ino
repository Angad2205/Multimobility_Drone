#include <SPI.h> // it is for serial interface commnication
#include <nRF24L01.h> // it is for NRF24LO1 MODULE
#include <RF24.h> // providing interface with with NRF24L01 module

const uint64_t pipeIn = 0xE8E8F0F0E1LL;// address of reciever pipe , use that in transmitter 
RF24 radio(10, 12); // chip select pin and chip enable pin

// The sizeof this struct should not exceed 32 bytes
struct Received_data { // created a class....
  byte ch1;  // variable chi which one byte....
};

int ch1_value = 0;
Received_data received_data; // here we created object of class

unsigned long last_Time = 0; // time when last pachet was recieved 
unsigned int frequency = 0; // frequency of communication

/**************************************************/

void setup()
{
  Serial.begin(9600);
  received_data.ch1 = 127;// initialise it with value 127
 
  //Once again, begin and radio configuration
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1,pipeIn);
  
  //We start the radio comunication
  radio.startListening();

}

/**************************************************/

//We create the function that will read the data each certain time
void receive_the_data()
{
  while ( radio.available() ) {
    radio.read(&received_data, sizeof(Received_data));//reading the data and updating recieved data
    last_Time = millis(); //Here we receive the data
  }
}

/**************************************************/

void loop()
{
  //Receive the radio data
  receive_the_data();
  
  // Calculate frequency
  unsigned long current_Time = millis();
  if (current_Time - last_Time != 0) {
    frequency = 1000 / (current_Time - last_Time); // Calculate frequency in Hz
  }
  
  ch1_value = map(received_data.ch1, 0, 255, 1000, 2000);
  
  // Display frequency and channel value
  Serial.print("Frequency: ");
  Serial.print(frequency);
  Serial.print(" Hz\t");
  Serial.print("Channel 1 Value: ");
  Serial.println(ch1_value);
  
  delay(100); // Delay to stabilize the output
}
