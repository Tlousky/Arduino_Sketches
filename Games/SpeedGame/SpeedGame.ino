// Variables and constants
const int input1       = 2;
const int input2       = 4;
const int Player1LED   = 3; // Player1's LED
const int Player2LED   = 5; // Player2's LED
const int IndicatorLED = 9; // Game's Indicator LED
boolean GameONSwitch   = false;

int p1Input, p2Input;

void setup() {
  pinMode(Player1LED,   OUTPUT      );    // declare LED as output
  pinMode(Player2LED,   OUTPUT      );    // declare LED as output
  pinMode(IndicatorLED, OUTPUT      );    // declare LED as output
  pinMode(input1,       INPUT_PULLUP);    // declare as PULLUP input
  pinMode(input2,       INPUT_PULLUP);    // declare as PULLUP input
}

void blink_3_times( int ledPin ) {
/* This function repeats 3 cycles of HIGH/LOW 
   outputs to the provided digital output pin 
*/
    for ( int i = 0; i <= 2; i++ ) {
        digitalWrite( ledPin, HIGH );
        delay( 50 );
        digitalWrite( ledPin, LOW );
        delay( 50 );
    }
}

void loop() {
    if ( GameONSwitch ) {
        p1Input = digitalRead( input1 );
        p2Input = digitalRead( input2 );

        // If one of the players pressed the key, 
        // Turn the game switch off to restart the game
        // On the next iteration of the loop function

        if ( ( p2Input == LOW ) || ( p1Input == LOW ) ) {
            // Game Over
            GameONSwitch = false;
        }
        
        if ( p2Input == LOW ) {
            blink_3_times( Player1LED );
        } else if ( p1Input == LOW ) {
            blink_3_times( Player2LED );
        }

    } else {
        // If the game is over, turn off the game indicator LED
        digitalWrite( IndicatorLED, LOW );

        // Delay between 1-5 seconds
        delay( random( 1, 5 ) * 1000 );
        
        // Turn game start LED and gameswitch flag on
        digitalWrite( IndicatorLED, HIGH );
        GameONSwitch = true;
    }
}
