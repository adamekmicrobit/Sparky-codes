#include <Servo.h>

// Piny
const int trigPin = 7;
const int echoPin = 6;
const int leftServoPin = 2;
const int rightServoPin = 3;
const int headPin = 10;
const int leftArmPin = 11;
const int rightArmPin = 12;

// Serva
Servo leftServo;
Servo rightServo;
Servo headServo;
Servo leftArm;
Servo rightArm;

// Kalibrace serv (90 = stop, >90 dopředu, <90 dozadu)
// Tyto hodnoty si můžeš doladit podle svého robota
const int forwardLeft = 120;   // levé kolo dopředu
const int forwardRight = 60;   // pravé kolo dopředu
const int backwardLeft = 60;   // levé kolo dozadu
const int backwardRight = 120; // pravé kolo dozadu
const int stopVal = 90;        // stop

// Ultrazvuk
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

// Pohyb kol
void goForward() { leftServo.write(forwardLeft); rightServo.write(forwardRight); }
void stopMoving() { leftServo.write(stopVal); rightServo.write(stopVal); }
void goBackward() { leftServo.write(backwardLeft); rightServo.write(backwardRight); }
void turnRight() { leftServo.write(forwardLeft); rightServo.write(backwardRight); }
void turnLeft()  { leftServo.write(backwardLeft); rightServo.write(forwardRight); }

// Animace hlavy a rukou
void headAndArmsReaction() {
  leftArm.write(180);
  rightArm.write(180);
  headServo.write(90);
  delay(300);

  headServo.write(180);
  delay(500);

  headServo.write(0);
  delay(500);

  headServo.write(90);
  delay(500);

  leftArm.write(90);
  delay(500);

  leftArm.write(180);
  rightArm.write(180);
  headServo.write(90);
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
  headServo.attach(headPin);
  leftArm.attach(leftArmPin);
  rightArm.attach(rightArmPin);

  headServo.write(90);
  leftArm.write(180);
  rightArm.write(180);

  stopMoving();
  delay(1000);
}

void loop() {
  long distance = getDistance();
  Serial.println(distance);

  if (distance < 15) {
    stopMoving();
    delay(300);

    headAndArmsReaction();

    goBackward();
    delay(700);
    stopMoving();
    delay(300);
    turnRight();
    delay(600);
    stopMoving();
    delay(300);
  } else {
    goForward();
  }

  delay(100);
}
