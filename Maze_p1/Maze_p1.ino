// =====================================================
// 3-Sensor Maze Robot
// Front Priority + Side Opening Detection
// =====================================================

// ---------------- MOTOR ----------------
const int IN1 = 5, IN2 = 6;
const int IN3 = 9, IN4 = 10;

// ---------------- ULTRASONIC ----------------
const int TF = 2, EF = 3;   // Front
const int TL = 4, EL = 7;   // Left
const int TR = 8, ER = 11;  // Right

// ---------------- THRESHOLDS ----------------
const int WALL  = 30;   // Side opening threshold
const int FRONT = 24;   // Front obstacle threshold

// ---------------- TURN TIMES ----------------
const unsigned long LEFT_TIME  = 350;
const unsigned long RIGHT_TIME = 350;
const unsigned long UTURN_TIME = 700;


// =====================================================
// STATES
// =====================================================

enum State {
  FORWARD,
  LEFT,
  RIGHT,
  UTURN
};

State state = FORWARD;

bool turning = false;

unsigned long actionStart;
unsigned long actionTime;


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(9600);

  // Motors
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Front sensor
  pinMode(TF, OUTPUT);
  pinMode(EF, INPUT);

  // Left sensor
  pinMode(TL, OUTPUT);
  pinMode(EL, INPUT);

  // Right sensor
  pinMode(TR, OUTPUT);
  pinMode(ER, INPUT);

  stopRobot();

  delay(1000);

  Serial.println("================================");
  Serial.println("       MAZE ROBOT READY");
  Serial.println("================================");

  moveForward();
}


// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // ---------------------------------------------------
  // FINISH TURN
  // ---------------------------------------------------

  if (turning) {

    if (millis() - actionStart >= actionTime) {

      turning = false;
      state = FORWARD;

      moveForward();

      Serial.println("ACTION: MOVE FORWARD");
    }

    return;
  }


  // ---------------------------------------------------
  // READ FRONT FIRST
  // ---------------------------------------------------

  float front = distance(TF, EF);


  Serial.print("Front: ");
  Serial.print(front, 0);
  Serial.print(" cm");


  // ===================================================
  // FRONT CLEAR
  // ===================================================

  if (front > FRONT) {

    // Keep moving forward.
    if (state != FORWARD) {

      state = FORWARD;

      moveForward();

      Serial.println(" | ACTION: MOVE FORWARD");
    }
    else {

      Serial.println(" | ACTION: FORWARD");
    }

    return;
  }


  // ===================================================
  // FRONT BLOCKED
  // ===================================================

  Serial.println(" | FRONT BLOCKED");


  // Now check the sides.
  delay(5);

  float left = distance(TL, EL);

  delay(5);

  float right = distance(TR, ER);


  Serial.print("Left: ");
  Serial.print(left, 0);

  Serial.print(" cm | Right: ");
  Serial.print(right, 0);

  Serial.println(" cm");


  // ===================================================
  // LEFT OPEN
  // ===================================================

  if (left > WALL) {

    startAction(LEFT);
  }


  // ===================================================
  // RIGHT OPEN
  // ===================================================

  else if (right > WALL) {

    startAction(RIGHT);
  }


  // ===================================================
  // NO SIDE OPEN
  // ===================================================

  else {

    startAction(UTURN);
  }


  delay(20);
}


// =====================================================
// START TURN
// =====================================================

void startAction(State newState) {

  state = newState;

  turning = true;

  actionStart = millis();


  switch (state) {

    case LEFT:

      turnLeft();

      actionTime = LEFT_TIME;

      Serial.println("ACTION: TURN LEFT");

      break;


    case RIGHT:

      turnRight();

      actionTime = RIGHT_TIME;

      Serial.println("ACTION: TURN RIGHT");

      break;


    case UTURN:

      turnAround();

      actionTime = UTURN_TIME;

      Serial.println("ACTION: U-TURN");

      break;


    case FORWARD:

      moveForward();

      turning = false;

      Serial.println("ACTION: MOVE FORWARD");

      break;
  }
}


// =====================================================
// MOTOR CONTROL
// =====================================================

void moveForward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void turnLeft() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void turnRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void turnAround() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void stopRobot() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


// =====================================================
// ULTRASONIC
// =====================================================

float distance(int trig, int echo) {

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  unsigned long t =
    pulseIn(echo, HIGH, 25000);


  // No echo = very far away
  if (t == 0)
    return 300;


  float d =
    t * 0.0343 / 2.0;


  return constrain(d, 2, 300);
}