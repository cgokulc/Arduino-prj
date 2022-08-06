//log_data.ino
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define THRESHOLD 20
#define READINGS_PER_SAMPLE 40

Adafruit_MPU6050 mpu;

int count =1;
float x_initial, y_initial, z_initial;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); 

  Serial.println("Adafruit MPU6050 test!");

  /* Try to initialize! */
  if (!mpu.begin(0x69)) {
    /* Serial.println("Failed to find MPU6050 chip"); */
    while (1) {
      delay(10);
    }
  }
  /* Serial.println("MPU6050 Found!"); */

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
  calibrate_mpu();
  
}

void loop() {
  detect_motion();
  
}

void read_data(){
  
  for(int i =0;i<40;i++){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
 
  Serial.print(a.acceleration.x );
  Serial.print(",");
  Serial.print(a.acceleration.y );
  Serial.print(",");
  Serial.println(a.acceleration.z);
  delay(10);
  }
  Serial.println("");
  Serial.println("--------");
  Serial.println(count);
  Serial.println("--------");
  count++;
}

void calibrate_mpu(){
  float totX, totY, totZ;
  sensors_event_t a, g, temp;
  
  
  for (int i = 0; i < 10; i++) {
    mpu.getEvent(&a, &g, &temp);
    totX = totX + a.acceleration.x;
    totY = totY + a.acceleration.y;
    totZ = totZ + a.acceleration.z;
  }
  x_initial = totX / 10;
  y_initial = totY / 10;
  z_initial = totZ / 10;
  Serial.println("Calibrated");
}

void detect_motion(){
   sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if( abs(a.acceleration.x - x_initial) +abs(a.acceleration.y - y_initial) + abs(a.acceleration.z - z_initial) > 15){
    read_data();
  }
  else{
    delay(5);
  }
}
