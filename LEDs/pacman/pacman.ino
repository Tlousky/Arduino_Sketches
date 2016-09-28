#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

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

const int r = 3;                       // Circle radius
const int center[]        = {  3, 3 };  // Circle center point (x,y)
const int tri_p1_offset[] = { -3, 4 };  // Triangle point 1 offset relative to circle center
const int tri_p2_offset[] = {  3, 4 };  // Triangle point 2 offset relative to circle center
const int eye_offset[]    = { -2, 0 };  // Eye point 1 offset relative to circle center

int p0_x, p0_y, p1_x, p1_y, p2_x, p2_y, eye_x, eye_y, i;

void loop() {
  // Draw base circle (main body of pacman)
  matrix.fillCircle( center[0], center[1], r, HIGH );

  p0_x = center[0];
  p0_y = center[1] + 1;

  // Calculate eye position relative to circle center
  eye_x = center[0] + eye_offset[0];
  eye_y = center[1] + eye_offset[1];
  matrix.drawPixel( eye_x, eye_y, LOW );

  // Calculate mouth triangle's 3 points relative to circle center
  p1_x = center[0] + tri_p1_offset[0];
  p1_y = center[1] + tri_p1_offset[1];
  p2_x = center[0] + tri_p2_offset[0];
  p2_y = center[1] + tri_p2_offset[1];
  matrix.fillTriangle( p0_x, p0_y, p1_x, p1_y, p2_x, p2_y, LOW );
  
  matrix.write();
}

// matrix.fillScreen(LOW);
// matrix.drawLine(x1, y1, x2, y2, HIGH);
// matrix.write();
