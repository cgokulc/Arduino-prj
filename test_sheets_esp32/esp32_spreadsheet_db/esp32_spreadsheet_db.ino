//Include required libraries
#include "WiFi.h"


// WiFi credentials
const char* ssid = "realme8";         // change SSID
const char* password = "12345678";    // change password

// Gscript ID and required credentials
const char *GScriptId = "AKfycbzDbFGFJemJPO6mXEfK8raOqQQ9SmTFLLS-RwKqk9SOSIB9feZYIYVeT3ByvVUZBGJ2tQ";    // change Gscript ID
const int httpsPort =  443;
const char* host = "script.google.com";
const char* googleRedirHost = "script.googleusercontent.com";
String url = String("/macros/s/") + GScriptId + "/exec?";
HTTPSRedirect client(httpsPort);

//
void startWiFi(){
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" IP address: ");
  Serial.println(WiFi.localIP());

  
  Serial.print(String("Connecting to "));
  Serial.println(host);

  bool WiFiFlag = false;
  for (int i=0; i<5; i++){
    int retval = client.connect(host, httpsPort);
    if (retval == 1) {
       WiFiFlag = true;
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }

  // Connection Status, 1 = Connected, 0 is not.
  Serial.println("Connection Status: " + String(client.connected()));
  Serial.flush();
  
  if (!WiFiFlag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    Serial.flush();
    return;
  }
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  delay(1000);
  // Start the DS18B20 sensor
  // connect to WiFi
  startWiFi();
}

void postData(String tag, float value){
  if (!client.connected()){
    Serial.println("Connecting to client again..."); 
    client.connect(host, httpsPort);
  }
  String urlFinal = url + "tag=" + tag + "&value=" + String(value);
  client.printRedir(urlFinal, host, googleRedirHost);

}

void loop(){
  Serial.print("inside");
  // Get temperature data
  //  get temperature data in C
  float temperatureC = 100.784;
  // post the data to google spreadsheet
  postData("Temperature", temperatureC);
  delay(5000);
}
