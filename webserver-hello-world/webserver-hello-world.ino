#include <WiFi.h>
#include <WebServer.h>

WebServer server;
int st = 0;
uint8_t pin_led = 4;
char* ssid = "realme8";
char* password = "12345678";

void setup()
{
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  server.on("/toggle",toggleLED);
  server.begin();
}

void loop()
{
  server.handleClient();
}

void toggleLED()
{ 
  if(st)
  {
    digitalWrite(pin_led,LOW);
    st =0;
  }
  else
  {
    digitalWrite(pin_led,HIGH);
    st = 1;
  }
  server.send(204,"");
}
