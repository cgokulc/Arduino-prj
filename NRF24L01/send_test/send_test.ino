#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>


#define CE_PIN  22
#define CSN_PIN 21

const byte thisSlaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
bool newData = false;

//===========

void setup()
{

   Serial.begin(115200);
   delay(3000);
   Serial.println("SimpleRx Starting");
   radio.begin();
   radio.setDataRate( RF24_250KBPS );
   radio.openReadingPipe(1, thisSlaveAddress);
   radio.stopListening();
}

//=============

void loop()
{
   sendData();
}

//==============

void sendData()
{
    uint8_t data[] = "And hello back to you";
    radio.write(data, sizeof(data));
    //radio.waitPacketSent();
    Serial.println("Sent a reply");
    delay(3000);
}
