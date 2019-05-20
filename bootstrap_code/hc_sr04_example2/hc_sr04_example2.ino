int trigPin = 2;//Trig – green Jumper
int echoPin = 3;    //Echo – yellow Jumper
long duration, cm, inches;
void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}
void loop() {
 digitalWrite(trigPin, LOW);
 delayMicroseconds(5);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 pinMode(echoPin, INPUT);
 duration = pulseIn(echoPin, HIGH);
 cm = (duration/2) / 29.1;
 inches = (duration/2) / 74;
 Serial.print(cm);
 Serial.println();
 delay(350); }
