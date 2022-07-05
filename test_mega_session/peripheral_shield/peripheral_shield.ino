// Connect peripheral board and dev board such that wifi and ble icon in peripheral board allign with cfi and elec club logo in dev board
// connect oled, mpu6050 and joystick to peripheral shield

#include <Arduino.h>
#include <U8g2lib.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


Adafruit_MPU6050 mpu;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);  

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  pinMode(32,INPUT);
  pinMode(33,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_4x6_tf);
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  u8g2.setCursor(5, 5);
  u8g2.print("Acc. X     : ");
  u8g2.println(a.acceleration.x);
  u8g2.setCursor(5, 12);
  u8g2.print("Acc. Y     : ");
  u8g2.println(a.acceleration.y);
  u8g2.setCursor(5, 19);
  u8g2.print("Acc. Z     : ");
  u8g2.println(a.acceleration.z);
  u8g2.setCursor(5, 26);
  u8g2.print("Joystick X : ");
  u8g2.println(analogRead(33));
  u8g2.setCursor(5, 33);
  u8g2.print("Joystick Y : ");
  u8g2.println(analogRead(32));
  u8g2.sendBuffer();
  delay(100);
}


//EXPECTED RESULT
//accelerations and joystick analog value updated and displayed on oled
