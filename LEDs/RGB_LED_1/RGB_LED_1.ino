// RGB LED Awesomeness

//                  r  g  b
int rgb_leds[3] = { 3, 6, 9 };

const int pushbutton = 13;
const int delay_time = 10;

int pushed = HIGH;
int r, g, b;

void setup() {
    // RGB LED pins
    for ( int i = 0; i <= 2; i++ ) {
      pinMode( rgb_leds[i], OUTPUT );      
    }
      
    // Pushbutton input pin
    pinMode( pushbutton, INPUT_PULLUP );
}

void loop() {

    // Read button input
    pushed = digitalRead( pushbutton );
    
    if (pushed == HIGH) {

        // Lift each LED color from 0 to 255 over a delay period
        for ( int led = 0; led <= 2; led++ ) {
            for ( int val = 0; val <= 255; val++ ) {
                analogWrite( rgb_leds[ led ], val );
                delay( delay_time );
            }
        }
        // Reduce each LED color from 255 to 0 over a delay period
        for ( int led = 0; led <= 2; led++ ) {
            for ( int val = 255; val >= 0; val-- ) {
                analogWrite( rgb_leds[ led ], val );
                delay( delay_time );
            }
        }

    } else {
        // Randomly draw a color each 100 ms
        int val;
        for ( int led = 0; led <= 2; led++ ) {
            val = random( 0, 255 );
            analogWrite( rgb_leds[ led ], val );
        }

        delay( 500 );
    }
}
