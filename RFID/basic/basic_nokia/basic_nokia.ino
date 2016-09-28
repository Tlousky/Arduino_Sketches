#include <SoftwareSerial.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>

SoftwareSerial RFID(2, 3); // RX and TX
 
// pin 7       - Serial clock out (SCLK)
// pin 6       - Serial data out (DIN)
// pin 5       - Data/Command select (D/C)
// pin 4/GND   - LCD chip select (CS)
// GND         - CE
// pin 3/RESET - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

int i, data1;
int clrln = 0;
int newtag[14];
String tag = "";
 
void setup() {
  RFID.begin(9600);    // start serial to RFID reader
  Serial.begin(9600);  // start serial to PC 
  
  // Start and set up Nokia 5110 Screen
  display.begin();
  display.setContrast(120);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);

  display.display();

}
 
void loop() {
  if (RFID.available() > 0) {
     
    for (int z = 0 ; z < 14 ; z++) {
        data1 = RFID.read();
        tag += data1;
    }
  
    RFID.flush(); // stops multiple reads
    display.clearDisplay();
    Serial.println( tag );
    
    // text display result
    display.println( tag );
    display.display();

    tag = "";
    delay(100);

  }
}
