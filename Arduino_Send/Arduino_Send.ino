//Send.ino

#include<SPI.h>
#include<RF24.h>

// ce, csn pins
RF24 radio(9, 10);

typedef struct{
  int accel_x;
  int accel_y;
  int accel_z;
} A_t;
A_t imu_data;

float accel_x,accel_y,accel_z;

void setup(void){
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  //radio.setDataRate(RF24_250KBPS);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();

  Serial.begin(9600);

}

void loop(void){
    accel_x = 5.05;
    accel_y = 22.01;
    accel_z = 10.07;
    
    imu_data.accel_x = (int)(100*accel_x);
    imu_data.accel_y = (int)(100*accel_y);
    imu_data.accel_z = (int)(100*accel_z);

    Serial.println("imu_data of x, y, z");
    Serial.println(imu_data.accel_x);
    Serial.println(imu_data.accel_y);
    Serial.println(imu_data.accel_z);
    bool stat = radio.write(&imu_data, sizeof(A_t));


  delay(5000);
}
