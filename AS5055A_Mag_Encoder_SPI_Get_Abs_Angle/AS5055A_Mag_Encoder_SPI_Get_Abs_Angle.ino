

/* The ESP32 has four SPi buses, however as of right now only two of
 * them are available to use, HSPI and VSPI. Simply using the SPI API 
 * as illustrated in Arduino examples will use VSPI, leaving HSPI unused.
 * 
 * However if we simply intialise two instance of the SPI class for both
 * of these buses both can be used. However when just using these the Arduino
 * way only will actually be outputting at a time.
 * 
 * Logic analyser capture is in the same folder as this example as
 * "multiple_bus_output.png"
 * 
 * created 30/04/2018 by Alistair Symonds
 */
#include <SPI.h>

// Define ALTERNATE_PINS to use non-standard GPIO pins for SPI bus


  #define HSPI_MISO   12
  #define HSPI_MOSI   13
  #define HSPI_SCLK   14
  #define HSPI_SS     25


static const int spiClk = 1000000; // 1 MHz

//uninitalised pointers to SPI objects
SPIClass * hspi = NULL;

void setup() {
  Serial.begin(115200);
  //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
  hspi = new SPIClass(HSPI);
  
  //clock miso mosi ss





  //initialise hspi with default pins
  //SCLK = 14, MISO = 12, MOSI = 13, SS = 15
  hspi->begin();

  //alternatively route through GPIO pins
  //hspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS); //SCLK, MISO, MOSI, SS


  //set up slave select pins as outputs as the Arduino API
  //doesn't handle automatically pulling SS low
  
  pinMode(HSPI_SS, OUTPUT); //HSPI SS
  digitalWrite(HSPI_SS, HIGH);
  set_gain();
}
//unsigned int time_now = 0;
//unsigned int count = 0;
unsigned short r;
// the loop function runs over and over again until power down or reset
void loop() {
  //use the SPI buses
  //vspiCommand();
//  if(time_now == 0)
//    time_now = millis();
//  else if(millis() - time_now > 1000)
//  {
//    Serial.println(count);
//    count = 0;
//    time_now = 0;
//  }
  //hspiCommand();
  get_abs_ang();
  //count++;
  //delay(10);
  //Serial.println(r);
}


uint16_t get_abs_ang()
{
  uint16_t result;
  uint16_t read_data, ang_data;
  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE1));
  digitalWrite(HSPI_SS, LOW);
  hspi->transfer(0xff);
  hspi->transfer(0xff);
  digitalWrite(HSPI_SS, HIGH);
  delayMicroseconds(10000);
  digitalWrite(HSPI_SS, LOW);
  result |= hspi->transfer(0x00) << 8;
  result |= hspi->transfer(0x00);
  digitalWrite(HSPI_SS, HIGH);
  hspi->endTransaction();
  //read_data =    (result & 0b1111111111111100) >> 2; 
  
  //bool mag_low =  result & 0b1000000000000000;
  //bool mag_high = result & 0b0100000000000000;
  ang_data =     (result & 0b0011111111111100) >> 2;
  //bool ef_flag =  result & 0b0000000000000010; 
  //bool par_flag = result & 0b0000000000000001;


//  Serial.print("Result: ");
//  Serial.println(result,BIN);
//  Serial.print("Read data: ");
//  Serial.println(read_data,BIN); 
//  Serial.print("Angular data: ");
  Serial.println(ang_data);
//  Serial.println("Flags : too low | too high | cmd_er | par : ");
//  Serial.print(mag_low);
//  Serial.print("\t");
//  Serial.print(mag_high);
//  Serial.print("\t");
//  Serial.print(ef_flag);
//  Serial.print("\t");
//  Serial.print(par_flag);
}

void set_gain()
{
  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE1));
  digitalWrite(HSPI_SS, LOW);
  hspi->transfer(0b0111111111110001);
  hspi->transfer(0b0000000011111101);
  hspi->transfer(0x0000);
  digitalWrite(HSPI_SS, HIGH);
  hspi->endTransaction();
}

// void hspiCommand() { 
//  uint16_t stuff = 0xffff;
//  uint16_t result;
//  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE1));
//  digitalWrite(HSPI_SS, LOW);
//  hspi->transfer(0xff);
//  hspi->transfer(0xff);
//  digitalWrite(HSPI_SS, HIGH);
//  delayMicroseconds(20);
//  digitalWrite(HSPI_SS, LOW);
//  result |= hspi->transfer(0x00) << 8;
//  result |= hspi->transfer(0x00);
//  digitalWrite(HSPI_SS, HIGH);
//  delayMicroseconds(20);
//  digitalWrite(HSPI_SS, LOW);
//  hspi->transfer(0b11100110) << 8;
//  hspi->transfer(0b10110101);
//  digitalWrite(HSPI_SS, HIGH);
//  delayMicroseconds(20);
//  digitalWrite(HSPI_SS, LOW);
//  hspi->transfer(0x00) << 8;
//  hspi->transfer(0x00);
//  digitalWrite(HSPI_SS, HIGH);
//  hspi->endTransaction();
//  Serial.println(result,BIN);
//}
