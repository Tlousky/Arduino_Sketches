// Constants and Variables

const int xpin       = A0;
const int ypin       = A1;
const int btnpin     = 2;
const int speakerpin = 9;

const int octave_multiplier = 2;

int vibnote = 5;

int xinput, yinput, btninput;

int idx, octave, vibrato;


//                C3   D3   E3   F3   G3   A3   B3
int notes[7] = { 130, 147, 165, 175, 196, 220, 247 };

void setup() {
    pinMode( btnpin,     INPUT_PULLUP );
    pinMode( speakerpin, OUTPUT       );
    Serial.begin( 9600 );
}

void loop() {  
    xinput   = analogRead( xpin );
    yinput   = analogRead( ypin );

    vibrato = digitalRead( btnpin ); // Since this is a pullup pin
    
    idx    = map( xinput, 0, 1023, 0, 6 );
    octave = map( yinput, 0, 1023, 1, 7 );

    String stridx = "Index: "; 
    String stroct = "Octave: "; 
    
    stridx += idx;
    stroct += octave;
    
    Serial.println( stridx );
    Serial.println( stroct );
    
    if (vibrato == LOW) {
      tone( speakerpin, notes[idx] * octave * octave_multiplier + vibnote );
      vibnote *= -1;
      delay( 50 );
    } else {
      tone( speakerpin, notes[idx] * octave * octave_multiplier );
    }
}
