//Send.ino

#include<SPI.h>
#include<RF24.h>

// ce, csn pins
RF24 radio(9, 10);

void setup(void){
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();
  Serial.begin(9600);
}

void loop(void){
    const char text[] = "Hello World is awesome";
    bool stat = radio.write(&text, sizeof(text));
   if (stat) {
        Serial.print("text send success!\n");
     }
     else{
        Serial.print("text send fail!\n");
        Serial.println(stat);
      }
  delay(5000);

}
