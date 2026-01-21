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

// Kalibrace serv
const int STOP = 90;
const int FWD_LEFT  = 120;
const int FWD_RIGHT = 60;
const int BWD_LEFT  = 60;
const int BWD_RIGHT = 120;

// Ultrazvuk
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 25000);
  if (duration == 0) return 999;

  long distance = duration * 0.034 / 2;
  return distance;
}

// Pohyb
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

// Reakce rukou (hlava se nehýbe)
void armsReaction() {
  leftArm.write(180);
  rightArm.write(180);
  delay(300);

  leftArm.write(90);
  delay(300);

  leftArm.write(180);
  rightArm.write(180);
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

  headServo.write(90);   // HLAVA STÁLE ROVNĚ
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

    armsReaction();

    // Couvání bez zatáčení dopředu
    goBackward();
    delay(700);

    stopMoving();
    delay(300);

    // Pokud chceš, můžeme i tohle vypnout
    // turnRight();  <-- odstraněno, robot nezatáčí
    // delay(600);

    stopMoving();
    delay(300);
  } 
  else {
    goForward();  // jede rovně bez zatáčení
  }

  delay(80);
}
