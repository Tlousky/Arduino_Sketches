void setup() { 
    Serial.begin( 9600 );
}

void loop() {
    float seconds = millis() / 1000;
    Serial.println( seconds );
    /*
    if ( seconds == int( seconds ) ) {
        Serial.println( seconds );
    }
    */
}

