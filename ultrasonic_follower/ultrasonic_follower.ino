int trigpin = 6;
int echopin = 9;

long duration;
int distance;


void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(echopin, LOW);

  duration = pulseIn(echopin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println(distance);

  if (distance <= 50 && distance >= 25) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    analogWrite(10, 90);
    analogWrite(11, 90);
  } else if (distance >= 15 && distance <= 25) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  } else if (distance <= 15) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    analogWrite(10, 90);
    analogWrite(11, 90);
  } else {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  delay(100);
}
