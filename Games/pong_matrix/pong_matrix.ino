#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <math.h>

#define spkr_pin 3
#define js_x     A0
#define js_y     A1
#define js_btn   2

const int line_width = 3;

int notes[]     = { 130, 164, 196, 196, 164, 164, 130, 164, 130, 98  };
int durations[] = { 250, 250, 250, 100, 250, 100, 150, 100, 150, 250 }; 
                                          //11            13      
int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays   = 1;

int x1, y1, x2, y2, px, py;
int xinput, yinput, btninput;
int base_pos[] = {7, 2};

int ball_x = 6, ball_y = 3;
boolean started = false;

int ball_dx = 1;
int ball_dy = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() {
  pinMode( js_btn,   INPUT_PULLUP );
  pinMode( spkr_pin, OUTPUT       );
  Serial.begin( 9600 ); 
  
  matrix.setIntensity(0);
  matrix.fillScreen(LOW);

  // Draw player line
  x1 = base_pos[0];
  y1 = base_pos[1];
  x2 = x1;
  y2 = y1 + line_width;  

  px = x1;
  py = y1;

  matrix.drawLine( x1, y1, x2, y2, HIGH );
  
  // Draw ball pixel
  matrix.drawPixel( ball_x, ball_y, HIGH );
  
  matrix.write();
}

void play_start_tune() {
  for ( int i = 0; i <= 9; i++ ) {
    tone( spkr_pin, notes[i], durations[i] );
    delay( durations[i] );
  }
  noTone( spkr_pin );
  
  delay(500); 
}

void read_joystick() {
  // Read joystick data
  xinput   = map( analogRead( js_x ), 0, 1023, -1, 2 );
  yinput   = map( analogRead( js_y ), 0, 1023, -1, 2 );
  btninput = digitalRead( js_btn );

  if ( ( btninput == 0 ) && ( ! started ) ) {
    play_start_tune();
    started = true;
  }

  x1 = px + yinput;
  y1 = py + xinput * -1;
  delay( 100 ); // Delay by 100ms to dilute sampling speed

  // Make sure line doesn't exit the screen
  if ( x1 > 7 ) { x1 = 7; }
  if ( x1 < 0 ) { x1 = 0; }
  if ( y1 + line_width > 7 ) { y1 = 7 - line_width; }
  if ( y1 < 0 ) { y1 = 0; }

  x2 = x1;
  y2 = y1 + line_width;
  
  px = x1; py = y1;  
}

void move_ball() {
  ball_x += ball_dx;
  ball_y += ball_dy;
  
  // These two conditions make sure ball direction is flipped if it hits a wall
  if ( ( ball_x + ball_dx > 7 ) ||  ( ball_x + ball_dx < 0 ) ) {
    ball_dx *= -1;
    tone( spkr_pin, 100, 50 );
  }
  if ( ( ball_y + ball_dy > 7 ) ||  ( ball_y + ball_dy < 0 ) ) {
    ball_dy *= -1;
    tone( spkr_pin, 100, 50 );
  }
  
  // This condition makes sure ball diretion is flipped if it hits the player
  if (( 
    ((( ball_x < x1 ) && ( ball_x + ball_dx >= x1 ) ) || ( ( ball_x > x1 ) && ( ball_x + ball_dx <= x1 ))) &&
    ( ( ball_y >= y1 ) && ( ball_y <= y2 ) )
    )) { 
      ball_dx *= -1;
      tone( spkr_pin, 250, 50 );
    }
}

void loop() {
  read_joystick();

  if ( started ) {
    move_ball();
  }

  matrix.fillScreen(LOW);
  matrix.drawLine( x1, y1, x2, y2, HIGH );  // Draw player
  matrix.drawPixel( ball_x, ball_y, HIGH ); // Draw ball pixel
  
  matrix.write();
}
