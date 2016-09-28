/* This sketch creates a siren with two modes, switched using a button.
   The first mode is a sound that progresses and regresses in noticable steps (default when the button is not pushed).
   The second mode is a continuous, classic siren.
   To get it to work you need to connect your speaker's (+) to pin9, and the button input to pin3, in a PULLUP configuration
   (connect the button's 2nd terminal to GND).
*/

// Variables and constants
const int speakerpin = 9;
const int btnpin     = 3;

int addtone, note, btnval, iterations, interval, midway;

void setup() {
  pinMode( speakerpin, OUTPUT       );
  pinMode( btnpin,     INPUT_PULLUP );
}

void loop() {
  btnval = digitalRead( btnpin );
  note    = 250;
  
  if ( btnval == LOW ) {
    addtone    = 5;
    iterations = 500;
    interval   = 5;
  } else {
    iterations = 100;
    addtone    = 25;
    interval   = 50;
  }
  
  midway = iterations / 2;
  for ( int i = 0; i <= iterations; i++ ) {
    note += addtone;
    tone( speakerpin, note );
    delay( interval );
    if ( i == midway ) {
      addtone *= -1;
    }
  }
}
