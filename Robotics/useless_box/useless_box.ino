#define DoorServoPin    5
#define TriggerServoPin 3
#define SwitchPin       2

#define DOOR_HOME    130
#define DOOR_OPEN    80
#define TRIGGER_HOME 179
#define TRIGGER_CLOSE 70

#include <Servo.h>

Servo DoorServo, TriggerServo;

int door_angle, trigger_angle, switch_val, randval;

void open_door( int door_delay, int spd, int after_delay ) {
  /* opens and closes the door after door_delay microseconds, as quickly as specified 
  in the fwdspd and bwdspd vars */
  
  int gap = DOOR_HOME - DOOR_OPEN;
  delay( door_delay );

  for ( int i = 0; i <= gap; i++ ) {
    DoorServo.write( DOOR_HOME - i );
    delay( spd );
  }
  
  delay( after_delay );  
}

void close_door( int door_delay, int spd, int after_delay ) {
  int gap = DOOR_HOME - DOOR_OPEN;
  delay( door_delay );
  
  for ( int i = 0; i <= gap; i ++ ) {
    DoorServo.write( DOOR_OPEN + i );
    delay( spd );
  }
  
  delay( after_delay );  
}

void trigger( int trigger_delay,  int fwdspd, int bwdspd, int between_delay, int after_delay ) {
  /* Sends the trigger arm towards the switch. Waits "delayval" milliseconds before starting.
     Forward movement speed is defined by forwardspeedval, and backward speed is defined by backwardspeedval.
  */

  int gap = TRIGGER_HOME - TRIGGER_CLOSE;
  delay( trigger_delay );

  for ( int i = 0; i <= gap; i++ ) {
    TriggerServo.write( TRIGGER_HOME - i );
    delay( fwdspd );
  }

  delay( between_delay );
  
  for ( int i = 0; i <= gap; i++ ) {
    TriggerServo.write( TRIGGER_CLOSE + i );
    delay( bwdspd );
  }
  
  delay( after_delay );
}

void peek_trigger() {
  open_door( 500, 15, 50 );

  // Move the trigger half the way to the switch
  int gap = ( TRIGGER_HOME - TRIGGER_CLOSE ) / 2;

  delay( 1000 );

  for ( int i = 0; i <= gap; i++ ) {
    TriggerServo.write( TRIGGER_HOME - i );
    delay( 10 );
  }

  delay( 250 );  
  
  TriggerServo.write( TRIGGER_HOME );
  delay( 100 );
  
  close_door( 150, 1, 50 );  
}

void open_close_cycle( int cycles, int spd, int delayval ) {
  for ( int i = 0; i < cycles; i++ ) {
    open_door(  delayval, spd, delayval );
    close_door( delayval, spd, delayval );
  }
}

// Door-Trigger sequence functions
void standard() {
  open_door( 500, 15, 50 );
  trigger( 500, 1, 15, 50, 50 );
  close_door( 500, 15, 50 );
}

void quick() {
  open_door(  250, 1, 15 );
  trigger(    25,  1,  1, 150, 25 );
  close_door( 100, 5, 15 );
}

void im_warning_you() {
  open_door(  250, 1, 15 );
  trigger(    25,  1,  15, 2000, 100 );
  close_door( 500, 15, 50 );
}

void im_warning_you_2() {
  open_close_cycle( 4, 2, 15 );
  open_door(  250, 1, 15 );
  for ( int i = 0; i < 2; i++ ) {
    trigger( 25, 1,  2, 25, 50 );
  }
  trigger( 25,  1,  15, 300, 100 );
  close_door( 500, 15, 50 );
}

void tease() {
  open_close_cycle( 2, 2, 25 );
  peek_trigger();
  standard(); 
}

void tease_2() {
  peek_trigger();
  quick();
}

void setup() {
  DoorServo.attach(    DoorServoPin    );
  TriggerServo.attach( TriggerServoPin );
  
  pinMode( SwitchPin, INPUT_PULLUP );

  DoorServo.write( DOOR_HOME );
  TriggerServo.write( TRIGGER_HOME );
  
  Serial.begin(9600);
}

void loop() {
  switch_val = digitalRead( SwitchPin );
  
  if (switch_val == HIGH ) {  
      randval = random( 1, 7 );
      switch (randval) {
        case 1:
          standard();
          break;
        case 2:
          quick();
          break;
        case 3:
          tease();
          break;
        case 4:
          tease_2();
          break;
        case 5:
          im_warning_you();
          break;
        case 6:
          im_warning_you_2();
          break;
      }
  }
}
