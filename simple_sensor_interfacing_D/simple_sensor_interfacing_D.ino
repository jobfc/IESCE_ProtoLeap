
int state = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(9, INPUT);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
 
  state = digitalRead(9);

  if (state == HIGH) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    analogWrite(10, 90);
    analogWrite(11, 90);
  }

  else {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }

}
