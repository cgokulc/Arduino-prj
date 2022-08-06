void setup() {
  // put your setup code here, to run once:
  pinMode(14, OUTPUT);
}

short i = 0;

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(14,i);
  i = ~i;
  delayMicroseconds(50000);
}
