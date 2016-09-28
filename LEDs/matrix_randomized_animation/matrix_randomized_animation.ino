#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <math.h>

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
  matrix.setIntensity(0);
  matrix.fillScreen(LOW);
}

int wait = 50;
int inc = -2;

const int corners[] = { 0, 7 };

int r, cx, cy, i, randval, fill;

void loop() {

  randval = round( random(0,2) );

  matrix.fillRect( 0,0,8,8, randval ); // Fill BG with light or no light randomly

  fill = randval;

  cx = corners[ round( random(0,2) ) ];
  cy = corners[ round( random(0,2) ) ];
  
  for ( int i = 1; i <= 7; i++ ) {
    if (fill == 0) {
      fill = 1;
    } else {
      fill = 0;
    }
      
    // Draw base circle (main body of pacman)
    matrix.drawCircle( cx, cy, i, fill );
    
    delay( 100 );
    
    matrix.write();
  }
}

// matrix.fillScreen(LOW);
// matrix.drawLine(x1, y1, x2, y2, HIGH);
// matrix.write();
