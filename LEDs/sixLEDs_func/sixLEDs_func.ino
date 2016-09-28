int pins[6] = { 2, 3, 4, 5, 6, 7 };

void light_pins( int duration ) {
  for ( int i = 0; i <= 5; i++ ) {
    digitalWrite( pins[i], HIGH );
    delay( duration );
    digitalWrite( pins[i], LOW );
  }
}

void setup() {
  for ( int i = 0; i <= 5; i++ ) {
    pinMode( pins[i], OUTPUT );
  }
}

void loop() {
  light_pins( 100 );
}
