#include <Servo.h>

Servo radarServo;

const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 9;

int angle = 15;
int direction = 1;

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);
  if (duration == 0) return 0;
  return (int)(duration * 0.0343 / 2);
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  radarServo.attach(servoPin);
  radarServo.write(angle);
  delay(400);
}

void loop() {
  radarServo.write(angle);
  delay(35); // allow servo to reach position

  int distance = measureDistance();

  // Format angle,distance (0 means no echo)
  Serial.print(angle);
  Serial.print(",");
  Serial.println(distance);

  angle += direction * 3;
  if (angle >= 165) {
    angle = 165;
    direction = -1;
  }
  if (angle <= 15) {
    angle = 15;
    direction = 1;
  }

  delay(35);
}
