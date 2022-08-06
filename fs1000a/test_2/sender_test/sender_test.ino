void setup() {
  // put your setup code here, to run once:
  pinMode(14, OUTPUT);
}

short i = 0;

void loop() {
  // put your main code here, to run repeatedly:
  for(i=0;i<256;i++)
  {
    dacWrite(DAC1, i);
    delay(100); 
  }
  for(i=255;i>0;i--)
  {
    dacWrite(DAC1, i);
    delay(100); 
  }
}
