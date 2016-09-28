// Constants and global variables
const int pitch_input    = A0;
const int duration_input = A1;
const int vibrato_input  = A2;
const int speaker_output = 9;

int pitch, duration, duration_mapped, note, vibrato;
int vibnote = 5;

//                C3   D3   E3   F3   G3   A3   B3   C4   D4   E4   F4   G4   A4   B4
int notes[14] = { 130, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494 };


void setup() {
    pinMode( speaker_output, OUTPUT );
    Serial.begin( 9600 );
}

void loop() {
    int vibrato_boolean;
  
    // Read LDRs from analog pins
    pitch    = analogRead( pitch_input    );
    duration = analogRead( duration_input );
    vibrato  = analogRead( vibrato_input  );

    // Translate analog range to 8 "digital" values
    note            = map( pitch,    0,   1023, 0, 13   );
    duration_mapped = map( duration, 500, 1023, 0, 5000 );
    vibrato_boolean = map( vibrato,  0,   1023, 0, 2    );
    
    Serial.println( vibrato );
    Serial.println( vibrato_boolean );
    Serial.println( );
    
    if ( duration_mapped <= 0 ) {
        noTone( speaker_output );
    } else {
        if (vibrato_boolean > 0) {
          tone( speaker_output, notes[ note ] + vibnote, duration_mapped );
          vibnote *= -1;
          delay( 50 );
        } else {
          tone( speaker_output, notes[ note ], duration_mapped );
        }
    }
}
