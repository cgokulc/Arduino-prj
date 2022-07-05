//connect dev board and motor shield, such that wifi and ble icon in motor shield allign with cfi and elec club logo in dev board
//connect motors to two output in motor shield

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
mpu.begin();
mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
mpu.setGyroRange(MPU6050_RANGE_500_DEG);
mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
pinMode(16,OUTPUT);
pinMode(17,OUTPUT);
pinMode(26,OUTPUT);
pinMode(27,OUTPUT);
pinMode(25,OUTPUT);
pinMode(14,OUTPUT);
digitalWrite(14,HIGH);
digitalWrite(25,HIGH);

digitalWrite(16,HIGH); //forward
digitalWrite(17,LOW);
delay(250);
digitalWrite(17,LOW); //backward
digitalWrite(16,LOW);
}

void loop() {

  
}

//EXPECTED OUTPUT 
// alternate forward n backward movement of motors
