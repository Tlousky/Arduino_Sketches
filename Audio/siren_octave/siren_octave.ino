// Variables and constants
const int speakerpin = 9;

//                C3   D3   E3   F3   G3   A3   B3   C4   D4   E4   F4   G4   A4   B4
int notes[14] = { 130, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494 };

void setup() {
  pinMode( speakerpin, OUTPUT );
}

void loop() {
  for ( int i = 0; i <= 25; i++ ) {
    if ( i <= 13 ) {
      tone( speakerpin, notes[i] );
    } else {
      tone( speakerpin, notes[25 - i] );
    }
    delay( 100 );
  }
}
