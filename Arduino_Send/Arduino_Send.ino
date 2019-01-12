//Send.ino

#include<SPI.h>
#include<RF24.h>

// ce, csn pins
RF24 radio(9, 10);

typedef struct{
  float accel_x;
  float accel_y;
  float accel_z;
  float gyro_x;
  float gyro_y;
  float gyro_z;
} A_t;
A_t imu_data;

void setup(void){
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();

  Serial.begin(9600);

}

void loop(void){
    imu_data.accel_x = 1.0;
    imu_data.accel_y = 2.0;
    imu_data.accel_z = 3.0;
    imu_data.gyro_x = 4.0;
    imu_data.gyro_y = 5.0;
    imu_data.gyro_z = 6.0;
    
    bool stat = radio.write(&imu_data, sizeof(imu_data));
    if (radio.write(&imu_data, sizeof(imu_data))) {
        Serial.print("data send success!\n");
     }
     else{
        Serial.print("data send fail!\n");
      }
  delay(5000);
}
