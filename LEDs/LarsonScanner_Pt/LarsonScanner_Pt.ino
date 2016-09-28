/* A Larson Scanner with speed controlled by a potentiometer */

int ledPins[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int topIdx  = 3;
int dir     = 1;
int topLed  = 0;

int ptDelay     = 0;
int mappedDelay = 0;

const int anlInput = 0;

void setup() {
    for ( int i = 0; i <= 7; i++ ) {
        pinMode(ledPins[i], OUTPUT );
    }
    
    pinMode( anlInput, INPUT );
}

void loop() {
    ptDelay = analogRead( anlInput );
    mappedDelay = map( ptDelay, 0, 1023, 0, 200 );
    delay( mappedDelay );

    // Turn off all LEDs
    for ( int i = 0; i <= 7; i++ ) { 
        digitalWrite( ledPins[i], LOW );
    }
    
    // Turn on 4 leds adjacent to topIdx
    for ( int i = 0; i <= 3; i++ ) {
        topLed = topIdx + i * dir;
        if (( topLed <= 7 ) || (  topLed >= 0 )) {
          digitalWrite( ledPins[ topLed ], HIGH );
        }
    }

    topIdx += dir;
    
    if ( ( topIdx == 7 ) || ( topIdx == 0 ) ) {
        dir *= -1;
    }
}
