#include <Servo.h>

// -----------------------------
// PINY
// -----------------------------
const int trigPin = 7;
const int echoPin = 6;

const int leftServoPin = 2;
const int rightServoPin = 3;

const int headPin = 10;
const int leftArmPin = 11;
const int rightArmPin = 12;

// -----------------------------
// SERVA
// -----------------------------
Servo leftServo;
Servo rightServo;
Servo headServo;
Servo leftArm;
Servo rightArm;

// -----------------------------
// KALIBRACE SERV
// (90 = stop, >90 dopředu, <90 dozadu)
// -----------------------------
const int STOP = 90;

const int FWD_LEFT  = 120;
const int FWD_RIGHT = 60;

const int BWD_LEFT  = 60;
const int BWD_RIGHT = 120;

// -----------------------------
// FUNKCE: MĚŘENÍ VZDÁLENOSTI
// -----------------------------
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 25000); // timeout 25 ms

  if (duration == 0) return 999; // nic nezměřeno → daleko

  long distance = duration * 0.034 / 2;
  return distance;
}

// -----------------------------
// FUNKCE POHYBU
// -----------------------------
void stopMoving() {
  leftServo.write(STOP);
  rightServo.write(STOP);
}

void goForward() {
  leftServo.write(FWD_LEFT);
  rightServo.write(FWD_RIGHT);
}

void goBackward() {
  leftServo.write(BWD_LEFT);
  rightServo.write(BWD_RIGHT);
}

void turnLeft() {
  leftServo.write(BWD_LEFT);
  rightServo.write(FWD_RIGHT);
}

void turnRight() {
  leftServo.write(FWD_LEFT);
  rightServo.write(BWD_RIGHT);
}

// -----------------------------
// ANIMACE HLAVY A RUKOU
// -----------------------------
void headAndArmsReaction() {
  leftArm.write(180);
  rightArm.write(180);
  headServo.write(90);
  delay(300);

  headServo.write(180);
  delay(400);

  headServo.write(0);
  delay(400);

  headServo.write(90);
  delay(400);

  leftArm.write(90);
  delay(300);

  leftArm.write(180);
  rightArm.write(180);
  headServo.write(90);
}

// -----------------------------
// SETUP
// -----------------------------
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

// -----------------------------
// HLAVNÍ LOOP
// -----------------------------
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

  delay(80);
}
