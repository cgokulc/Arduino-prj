void setup() {
  // put your setup code here, to run once:
  pinMode(14, INPUT);
  Serial.begin(115200);
}

short i;

void loop() {
  // put your main code here, to run repeatedly:
  i = analogRead(14);
  Serial.println(i);
  delay(50);
}
