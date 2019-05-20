// Libraries
#include <Nokia_LCD.h>

// Set up HC-SR04 pins and global variables
int trigPin = 2;
int echoPin = 3;
long duration, cm, inches;

// Set up Nokia 5110 LCD pins and variables
Nokia_LCD lcd(8 /* CLK */, 7 /* DIN */, 5 /* DC */, 4 /* CE */, 13 /* RST */);

void setup() {
  Serial.begin (9600);

  // Set up HC-SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up Nokia 5110
  lcd.begin();          // Initialize the screen
  lcd.setContrast(40);  // Set the contrast - Good values are usualy between 40 and 60
  lcd.clear(true);      // Clear the screen by filling it with black pixels
  lcd.setCursor(0, 5);  // Set the cursor on the beginning of the 6th row (the last one)
  lcd.print("Initializing..."); // Print text
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  
  duration = pulseIn(echoPin, HIGH);
  cm       = (duration/2) / 29.1;

  Serial.print(cm);
  Serial.println();

  // Print Distance to screen
  lcd.clear();          // Clear the screen by filling it with white pixels
  lcd.setCursor(0, 2);  // Set the cursor on the beginning of the 6th row (the last one)
  lcd.print("Distance: ");
  lcd.print(cm);
  lcd.print(" cm");
  
  delay(50); 
}
