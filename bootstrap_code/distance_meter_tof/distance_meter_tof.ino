// Libraries
#include <Nokia_LCD.h>
#include <SparkFun_RFD77402_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_RFD77402_Arduino_Library
RFD77402 ToF; //Hook object to the library

// Set up Nokia 5110 LCD pins and variables
Nokia_LCD lcd(8 /* CLK */, 7 /* DIN */, 5 /* DC */, 4 /* CE */, 13 /* RST */);

void setup() {
  Serial.begin (9600);

  if (ToF.begin() == false)
  {
    Serial.println("Sensor failed to initialize. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("Sensor online!");

  // Set up Nokia 5110
  lcd.begin();          // Initialize the screen
  lcd.setContrast(40);  // Set the contrast - Good values are usualy between 40 and 60
  lcd.clear(true);      // Clear the screen by filling it with black pixels
  lcd.setCursor(0, 5);  // Set the cursor on the beginning of the 6th row (the last one)
  lcd.print("Initializing..."); // Print text
}

void loop() {
  ToF.takeMeasurement(); //Tell sensor to take measurement
  byte errorCode = ToF.takeMeasurement();
  if (errorCode == CODE_VALID_DATA)
  {
    unsigned int distance = ToF.getDistance();
    byte pixels = ToF.getValidPixels();
    unsigned int confidence = ToF.getConfidenceValue();

    Serial.print("distance: ");
    Serial.print(distance);
    Serial.println("mm");
    Serial.print("pixels: ");
    Serial.println(pixels);
    Serial.print("confidence: ");
    Serial.println(confidence);

    // Print Distance to screen
    lcd.clear();          // Clear the screen by filling it with white pixels
    lcd.setCursor(0, 1);  // Set the cursor on the beginning of the 6th row (the last one)
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.println(" mm");
    lcd.print("Confidence: ");
    lcd.print(confidence);

  if(distance > 2000) Serial.print(" Nothing sensed");
  }
  else if (errorCode == CODE_FAILED_PIXELS)
  {
    Serial.print("Not enough pixels valid");
    lcd.print("Not enough pixels valid");
  }
  else if (errorCode == CODE_FAILED_SIGNAL)
  {
    Serial.print("Not enough signal");
    lcd.print("Not enough signal");
  }
  else if (errorCode == CODE_FAILED_SATURATED)
  {
    Serial.print("Sensor pixels saturated");
    lcd.print("Sensor pixels saturated");
  }
  else if (errorCode == CODE_FAILED_NOT_NEW)
  {
    Serial.print("New measurement failed");
    lcd.print("New measurement failed");
  }
  else if (errorCode == CODE_FAILED_TIMEOUT)
  {
    Serial.print("Sensors timed out");
    lcd.print("Sensors timed out");
  }
    
  delay(50); 
}
