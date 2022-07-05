long i, endd=100;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10000);
  Serial.println("RPi Pico @ 275 MHz");
  long Then, Now;
  for (int z =0; z<6 ; z++)
  { 
    i=0;
    Now = micros();
    for(long j=0;j<endd;j++)
     i+=j;
    Then = micros();
    endd*=10;
    Serial.print("Adding 1-");
    Serial.print(endd);
    Serial.print(" took (in us): ");
    Serial.println(Then-Now);
  }
  
}



void loop() {
  // put your main code here, to run repeatedly:
 Serial.println("----------");
 delay(5000);
}
