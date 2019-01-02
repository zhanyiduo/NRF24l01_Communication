#include <nRF24L01.h>
#include <printf.h>
#include <RF24_config.h>
#include<SPI.h>
#include<RF24.h>

// ce, csn pins
RF24 radio(9, 10);
const uint64_t pipes[2] = {0xF0F0F0F0E1LL,0xF0F0F0F0D2LL};

void setup(void){
	
  //Serial.begin(57600); //Debug 
  //printf_begin();
  //nRF24 configurations
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x4c);
  radio.setAutoAck(1);
  radio.setRetries(15,15);
  radio.setDataRate(RF24_250KBPS);
  radio.setPayloadSize(32);
  //radio.openReadingPipe(1,pipes[0]);
  radio.openWritingPipe(pipes[1]);
  radio.enableDynamicPayloads();
  radio.powerUp();
  radio.printDetails(); //for Debugging

}

void loop(void){
    const char text[] = "Hello World is awesome";
  radio.write(&text, sizeof(text));
  delay(1000);
}
