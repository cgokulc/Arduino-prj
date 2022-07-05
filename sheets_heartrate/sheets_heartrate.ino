/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <Wire.h>
#include "MAX30105.h"
//#include <Adafruit_BMP280.h>
#include "heartRate.h"

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;



MAX30105 particleSensor;
//Adafruit_BMP280 bmp; // I2C

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

int get_hr(){
    Serial.println("Place your index finger on the heart rate sensor with steady pressure.");
    long last = millis();
    while(millis()-last<10000)
    {
    long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
    
  }
    }
  beatAvg = map(beatAvg, 0, 120, 55, 85);
  Serial.print("HR: ");
  Serial.println(beatAvg);
return beatAvg;
}


//float get_temp()
//{
//  
//  Serial.println("Place your index finger on BMP280, getting temperature");
//  delay(1000);
//  float temp = bmp.readTemperature();
//  Serial.println("Temperature: ");
//  Serial.print(temp);
//  return temp;
//}


void loop() {
    // wait for WiFi connection

    
}

void setup() {
    wifiMulti.addAP("Sharanesh_One", "Sharanesh@56");
    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    

    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

//  int status = bmp.begin();
//  if (!status) {
//    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
//                      "try a different address!"));
//    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
//    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
//    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
//    Serial.print("        ID of 0x60 represents a BME 280.\n");
//    Serial.print("        ID of 0x61 represents a BME 680.\n");
//  }
  

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0xA0); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

//  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
//                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
//                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
//                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
//                  Adafruit_BMP280::STANDBY_MS_500); 

    Serial.println("Getting heartrate, please place your finger on sensor for 10 seconds");
  int val1 = get_hr();
//  float val2 = get_temp();
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;
        
        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        String url1 = "https://script.google.com/macros/s/AKfycbzDbFGFJemJPO6mXEfK8raOqQQ9SmTFLLS-RwKqk9SOSIB9feZYIYVeT3ByvVUZBGJ2tQ/exec?tag=heart-rate&value=";
        url1.concat(String(val1));
        http.begin(url1); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();

//        HTTPClient http1;
//        
//        USE_SERIAL.print("[HTTP] begin...\n");
//        // configure traged server and url
//        String url2 = "https://script.google.com/macros/s/AKfycbzDbFGFJemJPO6mXEfK8raOqQQ9SmTFLLS-RwKqk9SOSIB9feZYIYVeT3ByvVUZBGJ2tQ/exec?tag=temperature&value=";
//        url2.concat(String(val2));
//        http1.begin(url2); //HTTP
//
//        USE_SERIAL.print("[HTTP] GET...\n");
//        // start connection and send HTTP header
//        int http1Code = http1.GET();
//
//        // httpCode will be negative on error
//        if(http1Code > 0) {
//            // HTTP header has been send and Server response header has been handled
//            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
//
//            // file found at server
//            if(http1Code == HTTP_CODE_OK) {
//                String payload = http1.getString();
//                USE_SERIAL.println(payload);
//            }
//        } else {
//            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
//        }
//
//        http1.end();        
    }

 
  }
