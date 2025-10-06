#define trig A1
#define echo A0

#define enA 10
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define enB 5

#define MAX_DISTANCE 20
#define speed 130

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  // Send ultrasonic pulse
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  // Receive echo pulse
  duration = pulseIn(echo, HIGH);
  
  // Calculate distance
  distance = duration * 0.034 / 2;

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);

  // Check for obstacle within threshold distance
  if (distance <= MAX_DISTANCE) {
    // Obstacle detected, stop and move backward
    stopMotors();
    delay(500);
    moveBackward();
    delay(500);
    
    // Take a random turn (left or right)
    if (random(0, 2) == 0) {
      turnLeft();
    } else {
      turnRight();
    }
    delay(500);
  } else {
    // No obstacle, move forward
    moveForward();
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

