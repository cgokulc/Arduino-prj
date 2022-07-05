#include <esp_now.h>
#include <WiFi.h>

#define ledR 25
#define ledG 26
#define ledB 27



// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int r;
    int g;
    int b;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  ledcWrite(1, myData.r);
  ledcWrite(2, myData.g);
  ledcWrite(3, myData.b);
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("R: ");
  Serial.println(myData.r);
  Serial.print("G: ");
  Serial.println(myData.g);
  Serial.print("B: ");
  Serial.println(myData.b);
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  ledcAttachPin(ledR, 1); // assign RGB led pins to channels
  ledcAttachPin(ledG, 2);
  ledcAttachPin(ledB, 3);

  ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 12000, 8);
  ledcSetup(3, 12000, 8);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
