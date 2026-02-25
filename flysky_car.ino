#define chSpeed 34
#define chMove  35
#define chTurn  39

#define RPWM1 25
#define LPWM1 26
#define REN1  27
#define LEN1  14

#define RPWM2 32
#define LPWM2 33
#define REN2  12
#define LEN2  13

int speedLimit;
int moveValue;
int turnValue;

void setup() {

  Serial.begin(115200);

  pinMode(chSpeed, INPUT);
  pinMode(chMove, INPUT);
  pinMode(chTurn, INPUT);

  pinMode(REN1, OUTPUT);
  pinMode(LEN1, OUTPUT);
  pinMode(REN2, OUTPUT);
  pinMode(LEN2, OUTPUT);

  digitalWrite(REN1, HIGH);
  digitalWrite(LEN1, HIGH);
  digitalWrite(REN2, HIGH);
  digitalWrite(LEN2, HIGH);

  ledcAttach(RPWM1, 1000, 8);
  ledcAttach(LPWM1, 1000, 8);
  ledcAttach(RPWM2, 1000, 8);
  ledcAttach(LPWM2, 1000, 8);
}

void loop() {

  int speedPulse = pulseIn(chSpeed, HIGH, 25000);
  int movePulse  = pulseIn(chMove, HIGH, 25000);
  int turnPulse  = pulseIn(chTurn, HIGH, 25000);

  // Speed only positive (0–255)
  speedLimit = map(speedPulse, 1000, 2000, 0, 255);
  speedLimit = constrain(speedLimit, 0, 255);

  // Forward / Backward
  moveValue = map(movePulse, 1000, 2000, -255, 255);

  // Turning
  turnValue = map(turnPulse, 1000, 2000, -255, 255);

  // Deadband
  if (abs(moveValue) < 20) moveValue = 0;
  if (abs(turnValue) < 20) turnValue = 0;

  int leftMotor  = moveValue + turnValue;
  int rightMotor = moveValue - turnValue;

  // Limit by speed channel
  leftMotor  = constrain(leftMotor, -speedLimit, speedLimit);
  rightMotor = constrain(rightMotor, -speedLimit, speedLimit);

  driveMotor(RPWM1, LPWM1, leftMotor);
  driveMotor(RPWM2, LPWM2, rightMotor);
}

void driveMotor(int rpwm, int lpwm, int value) {

  if (value > 0) {
    ledcWrite(rpwm, value);
    ledcWrite(lpwm, 0);
  }
  else if (value < 0) {
    ledcWrite(rpwm, 0);
    ledcWrite(lpwm, abs(value));
  }
  else {
    ledcWrite(rpwm, 0);
    ledcWrite(lpwm, 0);
  }
}
