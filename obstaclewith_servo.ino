#include<Servo.h>
Servo myservo;
#define enA 10
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define enB 5

#define trigpin A0
#define echo A1
#define speed 150

void setup() {
  // Motor control pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(trigpin, OUTPUT);
  pinMode(echo, INPUT);

  // Set initial motor speed
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  // Attach servo motor
  myservo.attach(3);
  myservo.write(90); // Center position
  delay(3000);
}

int distance;

void loop() {
  // Measure distance using ultrasonic sensor
  findDistance();

  if (distance > 35) {
    forward();
  } else {
    delay(60);
    findDistance();
    if (distance > 35) {
      forward();
    } else {
      Stop();
      myservo.write(40);
      delay(500);
      findDistance();
      if (distance > 35) {
        myservo.write(90);
        delay(1000);
        rightward();
        delay(500);
        Stop();
      } else {
        myservo.write(130);
        delay(1000);
        findDistance();
        if (distance > 35) {
          myservo.write(90);
          delay(1000);
          leftward();
          delay(500);
          Stop();
        } else {
          myservo.write(90);
          delay(1000);
          rightward();
          delay(1500);
          Stop();
        }
      }
    }
  }
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void leftward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void rightward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void findDistance() {
  int duration;
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (1 / 29.1) * (duration / 2);
  delay(60);
}
