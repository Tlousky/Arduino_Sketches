#define red_pin   6
#define green_pin 5
#define blue_pin  3
#define RECV_PIN  11

#include <IRremote.h>

const int rgb_leds[] = { 6, 5, 3 };

const long r_less   = 16724175; // 1
const long r_more   = 16743045; // 3
const long g_less   = 16716015; // 4
const long g_more   = 16734885; // 6
const long b_less   = 16728765; // 7
const long b_more   = 16732845; // 9
const long randcol  = 16726215; // 
const long onoff    = 16753245; //
const long blinkrgb = 16718055; //

const int interval = 10;

int red   = 255;
int green = 255;
int blue  = 255;

long    ir_signal;
boolean onoff_switch     = true;
boolean randcolor_switch = false;

IRrecv irrecv(RECV_PIN);
decode_results results;

void blink_pin( int pin ) {
    analogWrite( pin, 100 );
    delay( 1000 );
    analogWrite( pin, 255 );
    delay( 1000 );     
}

void blink_rgb() {
  for ( int led = 0; led <= 2; led++ ) {
    blink_pin( rgb_leds[ led ] );
  }
}

void dimm_all() {
  for ( int led = 0; led <= 2; led++ ) {
    analogWrite( rgb_leds[ led ], 255 );
  }
}

void random_color() {
    // Randomly draw a color each 500 ms
    int val;
    
    for ( int led = 0; led <= 2; led++ ) {
        val = random( 0, 255 );
        analogWrite( rgb_leds[ led ], val );
    }

    delay( 500 );  
}

int inc_dec_val( char color, char action ) {
  int val = interval;
  if ( action == 'i' ) { val *= -1; }
  
  switch (color) {
    case 'r': val += red;   break;
    case 'g': val += green; break;
    case 'b': val += blue;  break;
  }
 
  if (val <= 0) {
    val = 0;
  } else if ( val >= 255 ) {
    val = 255;
  }

  switch (color) {
    case 'r': red   = val; break;
    case 'g': green = val; break;
    case 'b': blue  = val; break;   
  }

  return val;
}

void setup() {
  pinMode( red_pin, OUTPUT );
  pinMode( green_pin, OUTPUT );
  pinMode( blue_pin, OUTPUT );
  
  dimm_all();
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if ( irrecv.decode(&results) ) {
    ir_signal = results.value;
    Serial.println( ir_signal );

    switch (ir_signal) {
      case r_less:   
        analogWrite( red_pin, inc_dec_val( 'r', 'd' ) );
        break;
      case r_more:   
        analogWrite( red_pin, inc_dec_val( 'r', 'i' ) );
        break;
      case g_less:   
        analogWrite( green_pin, inc_dec_val( 'g', 'd' ) );
        break;
      case g_more:   
        analogWrite( green_pin, inc_dec_val( 'g', 'i' ) );
        break;
      case b_less:   
        analogWrite( blue_pin, inc_dec_val( 'b', 'd' ) );
        break;
      case b_more:   
        analogWrite( blue_pin, inc_dec_val( 'b', 'i' ) );
        break;
      case randcol:  
        randcolor_switch = ! randcolor_switch;
        break;
      case onoff:    
        onoff_switch = ! onoff_switch;
        if (! onoff_switch) { dimm_all(); }
        break;
      case blinkrgb: 
        blink_rgb();
        break;   
    }    
    
    ir_signal = 0;

    irrecv.resume(); // Receive the next value
  }
  
  if (randcolor_switch) { random_color(); }
}
