// Constants and Variables

const int xpin   = A0;
const int ypin   = A1;
const int btnpin = 2;

int xinput, yinput, btninput;

void setup() {
    pinMode( btnpin, INPUT_PULLUP );
    Serial.begin( 9600 );
}

void loop() {
    String x   = "X: ";
    String y   = "Y: ";
    String btn = "B: ";
  
    xinput   = analogRead( xpin );
    yinput   = analogRead( ypin );

    btninput = digitalRead( btnpin );
    
    x   = x   + xinput;
    y   = y   + yinput;
    btn = btn + btninput;

    //Serial.println( x   );
    //Serial.println( y   );
    Serial.println( btn );
    
    // 0    = max left
    // 511  = neutral center
    // 1023 = max right 
}
